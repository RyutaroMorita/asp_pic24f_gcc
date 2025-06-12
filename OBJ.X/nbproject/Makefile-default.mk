#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile).#
Device=PIC24FJ1024GB610
ProjectDir="C:\cygwin64\home\ryuta\asp_1.9.2\OBJ_pic24f.X"
ProjectName=OBJ_pic24f
ConfName=default
TOOLCHAIN_pic-as=C:\Program Files\Microchip\xc8\v2.31\pic-as\bin
TOOLCHAIN_AVRASM=C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avrassembler
TOOLCHAIN_XC32=C:\Program Files\Microchip\xc32\v4.30\bin
TOOLCHAIN_XC16=C:\Program Files\Microchip\xc16\v1.60\bin
TOOLCHAIN_ARM=C:\Program Files (x86)\GNU Tools ARM Embedded\10.3-2021.10\bin
TOOLCHAIN_XC8=C:\Program Files\Microchip\xc8\v2.31\bin
TOOLCHAIN_AVR=C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin
.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk image

# ------------------------------------------------------------------------------------
# Rules for buildStep: build and debug
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
image: C:/cygwin64/home/ryuta/asp_1.9.2/OBJ_pic24f/asp.exe nbproject/Makefile-default.mk 
else
image: C:/cygwin64/home/ryuta/asp_1.9.2/OBJ_pic24f/asp.exe nbproject/Makefile-default.mk 
endif

.PHONY: C:/cygwin64/home/ryuta/asp_1.9.2/OBJ_pic24f/asp.exe
C:/cygwin64/home/ryuta/asp_1.9.2/OBJ_pic24f/asp.exe: 
	cd ../OBJ_pic24f && OMIT_OPTIMIZATION=1 make

.PHONY: C:/cygwin64/home/ryuta/asp_1.9.2/OBJ_pic24f/asp.exe
C:/cygwin64/home/ryuta/asp_1.9.2/OBJ_pic24f/asp.exe: 
	cd ../OBJ_pic24f && make


# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	cd ../OBJ_pic24f && make realclean

