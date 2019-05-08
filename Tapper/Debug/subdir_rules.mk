################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
adc.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/adc.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="adc.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

buffer.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/buffer.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="buffer.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

buffer_printf.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/buffer_printf.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="buffer_printf.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

game.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/games/game.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="game.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hal_uart.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/hal/MSP430/MSP430F5529/hal_uart.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="hal_uart.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

json_parser.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/json_parser.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="json_parser.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

list.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/list.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="list.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

random_int.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/random_int.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="random_int.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

strcasecmp.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/strcasecmp.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="strcasecmp.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

subsystem.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/subsystem.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="subsystem.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

task.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/task.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="task.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

terminal.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/terminal.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="terminal.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

timing.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/timing.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="timing.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uart.obj: C:/Users/nklei/Documents/Homework/embedded\ software/embedded-software/src/uart.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/include" --include_path="C:/Users/nklei/Documents/Homework/embedded software/embedded-software/hal/MSP430/MSP430F5529" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/Users/nklei/Documents/Homework/embedded software/CCS/Klein_Game" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="uart.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


