#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile).
#
_/_=\\ShExtension=.batDevice=PIC24FJ1024GB610
ProjectDir="C:\cygwin64\home\RyutarouMorita\asp_pic24f_gcc\OBJ.X"
ProjectName=OBJ
ConfName=default
TOOLCHAIN_pic-as=C:\Program Files\Microchip\xc8\v3.00\pic-as\bin
TOOLCHAIN_XC16=C:\Program Files\Microchip\xc16\v2.10\bin
TOOLCHAIN_ARM=C:\SiliconLabs\SimplicityStudio\v5\developer\toolchains\gnu_arm\12.2.rel1_2023.7\bin
TOOLCHAIN_XC8=C:\Program Files\Microchip\xc8\v3.00\bin
#
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
ifeq (,$(findstring nbproject/Makefile-local-default.mk,$(MAKEFILES)))
MAKEFILES+=nbproject/Makefile-local-default.mk
endif
endif
endif
.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk image

# ------------------------------------------------------------------------------------
# Rules for buildStep: build and debug
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
image: C:/cygwin64/home/RyutarouMorita/asp_pic24f_gcc/OBJ/asp.exe nbproject/Makefile-default.mk 
else
image: C:/cygwin64/home/RyutarouMorita/asp_pic24f_gcc/OBJ/asp.exe nbproject/Makefile-default.mk 
endif

.PHONY: C:/cygwin64/home/RyutarouMorita/asp_pic24f_gcc/OBJ/asp.exe
C:/cygwin64/home/RyutarouMorita/asp_pic24f_gcc/OBJ/asp.exe: 
	cd ../OBJ && OMIT_OPTIMIZATION=1 make

.PHONY: C:/cygwin64/home/RyutarouMorita/asp_pic24f_gcc/OBJ/asp.exe
C:/cygwin64/home/RyutarouMorita/asp_pic24f_gcc/OBJ/asp.exe: 
	cd ../OBJ && make


# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	cd ../OBJ && make realclean

