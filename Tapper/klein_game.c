/*
 * tapper_game.c
 *
 *  Created on: Mar 18, 2019
 *      Author: Nicholas Klein
 *  Edited on: Mar 25, 2019
 *      Author: Nicholas Klein
 *
 *  Created using muh_game.c as a template
 *  Created on: Mar 29, 2014
 *      Author: Muhlbaier
 */
////////////////////////////MMmmbbbb

#include "project_settings.h"
#include "random_int.h"
#include "stddef.h"
#include "strings.h"
#include "game.h"
#include "timing.h"
#include "task.h"
#include "terminal.h"
#include "random_int.h"

#define MAP_WIDTH 30
#define MAP_HEIGHT 7
// times in ms
#define FIRE_SPEED 50
#define MIN_PATRON_TIME 3000/(MAP_WIDTH-1)
#define MAX_PATRON_TIME 12000/(MAP_WIDTH-1)
#define MIN_PATRON_RATE 1000
#define MAX_PATRON_RATE 8000

/// game structure
struct tapper_game_t {
    char y; ///< y coordinate of bartender
    char c; ///< character of bartender
    char glasses; ///< Number of glasses held
    int score; ///< score for the round
    int drinks_served; ///< drinks served during the round
    int glasses_bussed; ///< glasses bussed during the round
    uint8_t id; ///< ID of game=
};
#define MAX_GLASSES 3
#define MAX_PATRONS 3
static char_object_t patrons1[MAX_PATRONS];
static char_object_t patrons2[MAX_PATRONS];
static char_object_t patrons3[MAX_PATRONS];
static char_object_t FULL_GLASSES[MAX_GLASSES];
static char_object_t EMPTY_GLASSES[8];
static struct tapper_game_t game;

// note the user doesn't need to access these functions directly so they are
// defined here instead of in the .h file
// further they are made static so that no other files can access them
// ALSO OTHER MODULES CAN USE THESE SAME NAMES SINCE THEY ARE STATIC
static void Callback(int argc, char * argv[]);
static void Receiver(uint8_t c);

static void Play(void);
static void Help(void);
static void MoveRightPatron(char_object_t * o);
static void MoveLeftGlass(char_object_t * o);
static void MoveRightGlass(char_object_t * o);

static void Serve(void);
static void SendPatron(void);
static void GameOver(void);
static void MoveUp(void);
static void MoveDown(void);
static void CheckCollisionPatron(char_object_t * o);
static void CheckCollisionFull(char_object_t * o);
static void CheckCollisionEmpty(char_object_t * o);
static void DeletePatron(char_object_t * o);
static void DeleteFull(char_object_t * o);
static void DeleteEmpty(char_object_t * o);
static void ScorePoint(void);
static void UpdateGlasses(void);
static void ShowScore(void);

void TapperGame_Init(void) {
    // Register the module with the game system and give it the name "TAPPER3"
    game.id = Game_Register("TAPPER", "simple tapper", Play, Help);
    // Register a callback with the game system.
    // this is only needed if your game supports more than "play", "help" and "highscores"
    Game_RegisterCallback(game.id, Callback);
}

void Help(void) {
    Game_Printf("'a' and 's' or '<' and '>' to move the bartender up and down\r\n"
            "Move down while in the bottom space to grab full glasses\r\n"
            "SPACEBAR to Serve\r\n");
}

void Callback(int argc, char * argv[]) {
    // "play" and "help" are called automatically so just process "reset" here
    if(argc == 0) Game_Log(game.id, "too few args");
    if(strcasecmp(argv[0],"reset") == 0) {
        // reset scores
        game.score = 0;
        Game_Log(game.id, "Scores reset");
    }else Game_Log(game.id, "command not supported");
}

void Play(void) {
    volatile uint8_t i;
    // clear the screen
    Game_ClearScreen();
    // draw a box around our map
    Game_DrawRect(0, 0, MAP_WIDTH, MAP_HEIGHT);
    // draw the three bars
    Game_DrawRect(0, 2, MAP_WIDTH-3, 2);
    Game_DrawRect(0, 4, MAP_WIDTH-3, 4);
    Game_DrawRect(0, 6, MAP_WIDTH-3, 6);
    
    // initialize game variables
    for(i = 0; i < MAX_GLASSES; i++) FULL_GLASSES[i].status = 0;
    for(i = 0; i < 2*MAX_GLASSES; i++) EMPTY_GLASSES[i].status = 0;
    for(i = 0; i < MAX_PATRONS; i++) patrons1[i].status = 0;
    for(i = 0; i < MAX_PATRONS; i++) patrons2[i].status = 0;
    for(i = 0; i < MAX_PATRONS; i++) patrons3[i].status = 0;
    game.y = MAP_HEIGHT - 2;
    game.c = 't';
    game.glasses = MAX_GLASSES;
    game.score = 0;
    game.drinks_served = 0;
    game.glasses_bussed = 0;
    // draw the bartender at the bottom right of the map
    Game_CharXY(game.c, MAP_WIDTH - 1, game.y);
    Game_RegisterPlayer1Receiver(Receiver);
    // hide cursor
    Game_HideCursor();
    UpdateGlasses();
    ShowScore();
    // send first patron in 5 seconds
    // period is 0 because the task is rescheduled new each time at random intervals
    Task_Schedule(SendPatron, 0, 5000, 0);
}

void Receiver(uint8_t c) {
    switch (c) {
        case 's':
        case ',':
        case 'S':
        case '<':
            MoveDown();
            break;
        case 'w':
        case 'W':
        case '.':
        case '>':
            MoveUp();
            break;
        case ' ':
            Serve();
            break;
        case 'q':
        case 'Q':
            GameOver();
            break;
        default:
            break;
    }
}

void Serve(void) {
    static uint32_t last_fired;
    volatile uint8_t i;
    // pointer to glass to use
    char_object_t * full = 0;
    // make sure a glass was not just served
    if (TimeSince(last_fired) <= FIRE_SPEED) return;

    // find an unused glass
    for(i = 0; i < MAX_GLASSES; i++) if(FULL_GLASSES[i].status == 0) full = &FULL_GLASSES[i];
    if(full && game.glasses) {
        // schedule MoveUpShot1 to run every FIRE_SPEED ms, this is what makes the 't' move
        Task_Schedule((task_t)MoveLeftGlass, full, FIRE_SPEED, FIRE_SPEED);
        game.glasses--;
    }else { // if no fulls are left
        // indicate out of ammo by changing the pointer
        if (game.c == 't') {
            game.c = 'i';
            Game_CharXY(game.c,  MAP_WIDTH - 1, game.y);
        }
        return;
    }
    // change the status of the shot to indicate that it is used
    full->status = 1;
    // start the glass at the right just to the left of the bartender
    full->x = MAP_WIDTH - 2;
    full->y = game.y;
    full->c = 'U';
    Game_CharXY('t', MAP_WIDTH - 2, game.y);
    // track the time the last shot was fired so you can't have two on top of each other
    last_fired = TimeNow();
    UpdateGlasses();
}

void Return(char_object_t * full) {
    volatile uint8_t i;
    // pointer to glass to use
    char_object_t * empty = 0;
    for(i = 0; i < 2*MAX_GLASSES; i++) if(EMPTY_GLASSES[i].status == 0) empty = &EMPTY_GLASSES[i];
    // change the status of the shot to indicate that it is used
    empty->status = 1;
    empty->x = full->x+2;
    empty->y = full->y;
    empty->c = 'u';
    Task_Schedule((task_t)MoveRightGlass, empty, FIRE_SPEED*2, FIRE_SPEED*2);


}

void SendPatron(void) {
    char y;
    volatile uint8_t i;
    char_object_t * patron = 0;
    uint16_t right_period;
    // get random starting x location
    y = ((random_int(0, 5)/2) * 2) + 1;
    // get random time for moving right
    right_period = random_int(MIN_PATRON_TIME, MAX_PATRON_TIME);
    // find unused patron object
    switch (y) {
        case 1:
            for(i = 0; i < MAX_PATRONS; i++) if(patrons1[i].status == 0) patron = &patrons1[i];
            break;
        case 3:
            for(i = 0; i < MAX_PATRONS; i++) if(patrons2[i].status == 0) patron = &patrons2[i];
            break;
        case 5:
            for(i = 0; i < MAX_PATRONS; i++) if(patrons3[i].status == 0) patron = &patrons3[i];
            break;
    }
    if(patron) {
        patron->status = 1;
        patron->x = 1;
        patron->c = 'o';
        patron->y = y;
        // use the task scheduler to move the char right at the calculated period
        Task_Schedule((task_t)MoveRightPatron, patron, right_period, right_period);
        Game_CharXY('o', 1, y);
    }
    // schedule next patron to come between min and max patron rate
    // since a random time is desired the period is 0 so the task will be done when it us run
    // and a new task will be created at a different random time
    Task_Schedule(SendPatron, 0, random_int(MIN_PATRON_RATE/2, MAX_PATRON_RATE/2), 0);
}

void MoveUp(void) {
    // make sure we can move right
    if (game.y > 1) {
        // clear location
        Game_CharXY(' ', MAP_WIDTH - 1, game.y);
        if (game.y == 2){
            game.y--;
        }
        else {
            game.y = game.y - 2;
        }
        // update
        Game_CharXY(game.c, MAP_WIDTH - 1, game.y);
    }

}

void MoveDown(void) {
    // make sure we can move right
    if (game.y < MAP_HEIGHT - 3) {
        // clear location
        Game_CharXY(' ',  MAP_WIDTH - 1, game.y);
        if (game.y == MAP_WIDTH - 2){
            game.y++;
        }
        else {
            game.y =  game.y + 2;
        }
        // update
        Game_CharXY(game.c, MAP_WIDTH - 1, game.y);
    }
    else {
        game.glasses = 3;
        UpdateGlasses();
    }
}

void MoveRightPatron(char_object_t * o) {
    // first make sure we can move right
    if (o->x < MAP_WIDTH - 1) {
        // clear location
        Game_CharXY(' ', o->x, o->y);
        // update x position
        o->x++;
        // re-print
        Game_CharXY(o->c, o->x, o->y);
        CheckCollisionPatron(o);
    } else {
        GameOver();
    }
}


void MoveLeftGlass(char_object_t * o) {
    // first make sure we can move right
    if (o->x > 1) {
        // clear location
        Game_CharXY(' ', o->x, o->y);
        // update x position
        o->x--;
        // re-print
        Game_CharXY(o->c, o->x, o->y);
        CheckCollisionFull(o);
    } else {
        // clear the glass
        Game_CharXY(' ', o->x, o->y);
        DeleteFull(o);
    }
}

static void MoveRightGlass(char_object_t * o) {
    // first make sure we can move right
    if (o->x < MAP_WIDTH - 1) {
        // clear location
        Game_CharXY(' ', o->x, o->y);
        // update x position
        o->x++;
        // re-print
        Game_CharXY(o->c, o->x, o->y);
        CheckCollisionEmpty(o);
    } else {
        // clear the glass
        Game_CharXY(' ', o->x, o->y);
        DeleteEmpty(o);
    }
}

void CheckCollisionPatron(char_object_t * patron) {
    volatile uint8_t i;
    char_object_t * full;
    for(i = 0; i < MAX_GLASSES; i++) {
        full = &FULL_GLASSES[i];
        if(full->status) {
            if (patron->x == full->x && patron->y == full->y) {
                DeletePatron(patron);
                Return(full);
                DeleteFull(full);
                // put a c where the collision happened
                Game_CharXY('c', patron->x, patron->y);
                game.drinks_served++;
                ScorePoint();
            }
        }
    }
}

void CheckCollisionFull(char_object_t * full) {
    volatile uint8_t i;
    char_object_t * patron;
    for(i = 0; i < MAX_PATRONS; i++) {
        patron = &patrons1[i];
        if(patron->status) {
            if (patron->x == full->x && patron->y == full->y) {
                DeletePatron(patron);
                Return(full);
                DeleteFull(full);
                // put a c where the collision happened
                Game_CharXY('c', patron->x, patron->y);
                game.drinks_served++;
                ScorePoint();
            }
        }
        patron = &patrons2[i];
        if(patron->status) {
            if (patron->x == full->x && patron->y == full->y) {
                DeletePatron(patron);
                Return(full);
                DeleteFull(full);
                // put a c where the collision happened
                Game_CharXY('c', patron->x, patron->y);
                game.drinks_served++;
                ScorePoint();
            }
        }
        patron = &patrons3[i];
        if(patron->status) {
            if (patron->x == full->x && patron->y == full->y) {
                DeletePatron(patron);
                Return(full);
                DeleteFull(full);
                // put a c where the collision happened
                Game_CharXY('c', patron->x, patron->y);
                game.drinks_served++;
                ScorePoint();
            }
        }
    }
}

void CheckCollisionEmpty(char_object_t * empty) {
    volatile uint8_t i;
    if (empty->x >= MAP_WIDTH-1) {
        if (game.y == empty->y) {
            DeleteFull(empty);
            game.glasses_bussed++;
            ScorePoint();
        }
        else {
            DeleteFull(empty);
        }
    }
    Game_CharXY(game.c, MAP_WIDTH - 1, game.y);
}

void ScorePoint(void) {
    game.score++;
    // sound the alarm
    Game_Bell();
    ShowScore();
}

// if o is 0 then delete all enemies
void DeletePatron(char_object_t * o) {
    // set status to 0
    if(o) o->status = 0;
    // remove the tasks used to move the patron
    Task_Remove((task_t)MoveRightPatron, o);
}

// if o is 0 then delete all fulls
void DeleteFull(char_object_t * o) {
    // set status to 0
    if(o) o->status = 0;
    // remove the tasks used to move the shot
    Task_Remove((task_t)MoveLeftGlass, o);
}

// if o is 0 then delete all empties
void DeleteEmpty(char_object_t * o) {
    // set status to 0
    if(o) o->status = 0;
    // remove the tasks used to move the shot
    Task_Remove((task_t)MoveRightGlass, o);
}

void UpdateGlasses(void) {
    Game_CharXY('\r', 0, MAP_HEIGHT + 2);
    Game_Printf("Glasses: ");
    if(game.glasses >= 3) Game_Printf("U U U");
    else if(game.glasses == 2) Game_Printf("U U  ");
    else if(game.glasses == 1) Game_Printf("U    ");
    else if(game.glasses == 0) Game_Printf("     ");

    game.c = 't';
}

void ShowScore(void) {
    Game_CharXY('\r', 0, MAP_HEIGHT + 3);
    Game_Printf("Score: ");
    Game_Printf("%i", game.score);
    Game_CharXY('\r', 0, MAP_HEIGHT + 4);
    Game_Printf("Served: ");
    Game_Printf("%i", game.drinks_served);
    Game_Printf("    Bussed: ");
    Game_Printf("%i", game.glasses_bussed);
}

void GameOver(void) {
    // clean up all scheduled tasks
    DeleteFull(0);
    DeleteEmpty(0);
    DeletePatron(0);
    Task_Remove(SendPatron, 0);
    // if a controller was used then remove the callbacks
    // set cursor below bottom of map
    Game_CharXY('\r', 0, MAP_HEIGHT + 1);
    // show score
    Game_Printf("Game Over!\r\n");
    //Game_Printf("Game Over! Final score: %d\r\nTotal Drinks Served: %d", game.score, game.drinks_served);
    // unregister the receiver used to run the game
    Game_UnregisterPlayer1Receiver(Receiver);
    // show cursor (it was hidden at the beginning
    Game_ShowCursor();
    Game_GameOver();
}
