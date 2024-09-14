.SUFFIXES: # Clear list
.EXTENSIONS: .obj .asm .c .exe .lib

#
#  Target Options
#
NLMNAME      = LISTNLM
NLMOBJS      = listnlm.obj
NLMVERSION   = 1.0.0
NLMMESSAGE   = 'LISTNLM - LIST LOADED MODULES'
NLMCOPYRIGHT = '(c) Copyright 2006 0xbadc0ded\0'

#
#  Compiler Flags
#
INCLUDE  = -I..\sdk\include
CFLAGS   = -w2 -e25 -zp4 -zq -of -or -mf -5s -s -bt=nios $(INCLUDE)
ASMFLAGS = -5

#
#  Compiler commands
#
.asm.obj: .AUTODEPEND
		wasm $(ASMFLAGS) $<

.c.obj: .AUTODEPEND
		wcc386 $(CFLAGS) $<

#
#  Targets
#
all: $(NLMNAME).nlm

#
#  Rules
#
$(NLMNAME).lnk: $(NLMOBJS) .ALWAYS
    %create $^@
    @%append $^@ FORMAT     NOVELL NLM $(NLMMESSAGE)
    @%append $^@ IMPORT     @$(NLMNAME).IMP
    @%append $^@ NAME       $(NLMNAME).NLM
    @%append $^@ OP MAP
    @%append $^@ OP NOD
    @%append $^@ OP START = NlmMain
    @%append $^@ OP CHECK = NlmCheckUnload
    @%append $^@ OP EXIT  = NlmExit
    @%append $^@ OP VERS  = $(NLMVERSION)
    @%append $^@ OP COPYR = $(NLMCOPYRIGHT)
    for %i in ($(NLMOBJS)) do @%append $^@ FILE %i

$(NLMNAME).nlm: $(NLMOBJS) $(NLMNAME).lnk
    wlink @$(NLMNAME).lnk

clean: .SYMBOLIC
    -@del $(NLMNAME).lnk
    -@del $(NLMNAME).map
    -@del $(NLMNAME).nlm
    -@del *.obj
