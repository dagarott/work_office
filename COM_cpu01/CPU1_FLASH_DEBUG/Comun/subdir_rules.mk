################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Comun/F2837xD_DefaultISR.obj: C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/Comun/F2837xD_DefaultISR.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/ti-cgt-c2000_16.9.6.LTS/include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/F2837xD_common/include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/F2837xD_headers/include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/COM_cpu01/Include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/Comun/Drivers/Include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/Comun/driverlib" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="Comun/F2837xD_DefaultISR.d_raw" --obj_directory="Comun" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Comun/F2837xD_GlobalVariableDefs.obj: C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/Comun/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/ti-cgt-c2000_16.9.6.LTS/include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/F2837xD_common/include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/F2837xD_headers/include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/COM_cpu01/Include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/Comun/Drivers/Include" --include_path="C:/Users/jeniher/PROYECTOS/Workspace_CCS7/UFCharger/F2837xD/Comun/driverlib" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="Comun/F2837xD_GlobalVariableDefs.d_raw" --obj_directory="Comun" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


