let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd e:\projects\Waves\Waves
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 SimWire.h
badd +456 SimWire.cpp
badd +33 SimGraphInterface.h
badd +1 todo.txt
badd +1 UnitTests
badd +1 SimNode.cpp
badd +1 simtest.cpp
badd +30 TestSim.cpp
badd +76 TestSimInitializer.cpp
badd +23 SimInitializer.cpp
badd +1 SimInitializer.h
badd +25 SimController.h
badd +37 SimController.cpp
badd +1 \programs\vim\_vimrc
badd +1 ~\vimfiles\after\ftplugin\txt.vim
badd +2 ~\vimfiles\after\ftplugin\asm.vim
badd +1 $.VIM
badd +1 $VIMFILES
badd +1 ~\.
badd +1 Mouseable.h
badd +2 FrameUpdateDispatcher.h
badd +7 Mouseable.cpp
badd +17 EventDispatcher.h
badd +34 GUISimControlsWindow.h
badd +1 GUISimControlsWindow.cpp
badd +54 HeatWave.cpp
badd +36 Wire.cpp
badd +5 TestMouseable.cpp
badd +11 Mouseable.txt
badd +1 HeatWave.h
badd +1 TestMouseable.h
badd +31 Selectable.h
badd +10 Selectable.cpp
badd +1 Selectable.txt
badd +1 SelectionController.h
badd +1 SelectionController.cpp
badd +27 DrawWire.h
badd +1 DrawWire.cpp
badd +18 sfLine.h
badd +9 sfLine.cpp
badd +1 VectorOps.h
badd +16 VectorOps.cpp
badd +1 -TaskList_23-
badd +1 -TaskList_47-
badd +1 -TaskList_48-
badd +18 ipython\ -\ 1
badd +229 ~\vimfiles\bundle\Conque-Shell\doc\conque_term.txt
badd +24 ipython\ -\ 2
badd +1 ~\_vimrc
badd +1 ~\vimfiles\bundles\ .
badd +1 ~\vimfiles\bundles
badd +263 ~\vimfiles\bundle\Conque-Shell\autoload\conque_term\conque_globals.py
badd +1 powershell\ -\ 3
badd +33 ~\vimfiles\bundle\Conque-Shell\plugin\conque_term.vim
badd +39 ~\vimfiles\bundle\Conque-Shell\autoload\conque_term.vim
badd +1 ~\vimfiles\bundle\Conque-Shell\syntax\conque_term.vim
badd +8 powershell\ -\ 1
badd +225 ~\vimfiles\bundle\vim-wasabi-colorscheme\colors\wasabi256.vim
badd +1 ~\bundle
badd +1 powershell\ -\ 2
badd +1 c:\programs\vim\vim74\autoload
badd +3795 \programs\vim\vim74\autoload\netrw.vim
badd +1 DrawWireSelectMouseable.h
badd +0 WireSelectMouseable.cpp
badd +0 WireSelectMouseable.h
argglobal
silent! argdel *
argadd SimWire.cpp
set stal=2
edit SimNode.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 37 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 102 + 137) / 274)
exe '2resize ' . ((&lines * 25 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 102 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 169 + 137) / 274)
exe '4resize ' . ((&lines * 33 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 169 + 137) / 274)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\todo.txt
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 6 - ((5 * winheight(0) + 12) / 25)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
6
normal! 060|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\SimWire.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 456 - ((0 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
456
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\SimWire.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 49 - ((0 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
49
normal! 05|
lcd e:\projects\Waves\Waves
wincmd w
exe '1resize ' . ((&lines * 37 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 102 + 137) / 274)
exe '2resize ' . ((&lines * 25 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 102 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 169 + 137) / 274)
exe '4resize ' . ((&lines * 33 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 169 + 137) / 274)
tabedit e:\projects\Waves\Waves\SimInitializer.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
set nosplitbelow
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 80 + 137) / 274)
exe '2resize ' . ((&lines * 19 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 109 + 137) / 274)
exe '3resize ' . ((&lines * 44 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 109 + 137) / 274)
exe 'vert 4resize ' . ((&columns * 83 + 137) / 274)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 32) / 64)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\SimInitializer.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 9) / 19)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\SimController.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 22) / 44)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\SimController.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 32) / 64)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
exe 'vert 1resize ' . ((&columns * 80 + 137) / 274)
exe '2resize ' . ((&lines * 19 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 109 + 137) / 274)
exe '3resize ' . ((&lines * 44 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 109 + 137) / 274)
exe 'vert 4resize ' . ((&columns * 83 + 137) / 274)
tabedit e:\projects\Waves\Waves\HeatWave.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 30 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 88 + 137) / 274)
exe '2resize ' . ((&lines * 33 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 88 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 103 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 103 + 137) / 274)
exe '5resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 81 + 137) / 274)
exe '6resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 81 + 137) / 274)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 35 - ((21 * winheight(0) + 15) / 30)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
35
normal! 074|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\TestMouseable.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 012|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\HeatWave.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 16 - ((15 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
16
normal! 026|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\Mouseable.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\FrameUpdateDispatcher.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 17 - ((16 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
17
normal! 02|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\Mouseable.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 19 - ((1 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
19
normal! 09|
lcd e:\projects\Waves\Waves
wincmd w
exe '1resize ' . ((&lines * 30 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 88 + 137) / 274)
exe '2resize ' . ((&lines * 33 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 88 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 103 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 103 + 137) / 274)
exe '5resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 81 + 137) / 274)
exe '6resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 81 + 137) / 274)
tabedit e:\projects\Waves\Waves\Selectable.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 38 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 86 + 137) / 274)
exe '2resize ' . ((&lines * 25 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 86 + 137) / 274)
exe '3resize ' . ((&lines * 30 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 83 + 137) / 274)
exe '4resize ' . ((&lines * 33 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 83 + 137) / 274)
exe '5resize ' . ((&lines * 31 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 103 + 137) / 274)
exe '6resize ' . ((&lines * 32 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 103 + 137) / 274)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 19) / 38)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\Selectable.txt
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 2 - ((1 * winheight(0) + 12) / 25)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
2
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\Selectable.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 10 - ((9 * winheight(0) + 15) / 30)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
10
normal! 025|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
enew
file e:\projects\Waves\Waves\powershell\ -\ 1
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\SelectionController.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 11 - ((10 * winheight(0) + 15) / 31)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
11
normal! 09|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\SelectionController.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 30 - ((15 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
30
normal! 041|
lcd e:\projects\Waves\Waves
wincmd w
exe '1resize ' . ((&lines * 38 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 86 + 137) / 274)
exe '2resize ' . ((&lines * 25 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 86 + 137) / 274)
exe '3resize ' . ((&lines * 30 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 83 + 137) / 274)
exe '4resize ' . ((&lines * 33 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 83 + 137) / 274)
exe '5resize ' . ((&lines * 31 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 103 + 137) / 274)
exe '6resize ' . ((&lines * 32 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 103 + 137) / 274)
tabedit e:\projects\Waves\Waves\DrawWire.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 44 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 80 + 137) / 274)
exe '2resize ' . ((&lines * 19 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 80 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 97 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 97 + 137) / 274)
exe '5resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 95 + 137) / 274)
exe '6resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 95 + 137) / 274)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 22) / 44)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\VectorOps.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 9 - ((8 * winheight(0) + 9) / 19)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
9
normal! 040|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\DrawWire.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\HeatWave.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 54 - ((33 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
54
normal! 012|
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\WireSelectMouseable.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 9 - ((8 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
9
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
argglobal
edit e:\projects\Waves\Waves\WireSelectMouseable.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
5wincmd w
exe '1resize ' . ((&lines * 44 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 80 + 137) / 274)
exe '2resize ' . ((&lines * 19 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 80 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 97 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 97 + 137) / 274)
exe '5resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 95 + 137) / 274)
exe '6resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 95 + 137) / 274)
tabnext 5
set stal=1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
