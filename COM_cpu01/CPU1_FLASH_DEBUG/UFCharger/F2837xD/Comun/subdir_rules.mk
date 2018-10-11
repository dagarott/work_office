################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
UFCharger/F2837xD/Comun/F2837xD_DefaultISR.obj: C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/Comun/F2837xD_DefaultISR.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/ti-cgt-c2000_16.9.6.LTS/include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/F2837xD_common/include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/F2837xD_headers/include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/COM_cpu01/Include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/Comun/Drivers/Include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/Comun/driverlib" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="UFCharger/F2837xD/Comun/$(basename $(<F)).d_raw" --obj_directory="UFCharger/F2837xD/Comun" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UFCharger/F2837xD/Comun/F2837xD_GlobalVariableDefs.obj: C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/Comun/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/ti-cgt-c2000_16.9.6.LTS/include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/F2837xD_common/include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/F2837xD_headers/include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/COM_cpu01/Include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/Comun/Drivers/Include" --include_path="C:/Users/dagaro/workspace/Firmware_Test/UFCharger/F2837xD/Comun/driverlib" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="UFCharger/F2837xD/Comun/$(basename $(<F)).d_raw" --obj_directory="UFCharger/F2837xD/Comun" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


