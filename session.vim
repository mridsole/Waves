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
badd +1 Selectable.h
badd +45 Selectable.cpp
badd +1 Selectable.txt
badd +1 SelectionController.h
badd +1 SelectionController.cpp
badd +1 DrawWire.h
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
badd +225 ~\vimfiles\bundle\vim-wasabi-colorscheme\colors\wasabi256.vim
badd +1 ~\bundle
badd +1 powershell\ -\ 2
badd +1 c:\programs\vim\vim74\autoload
badd +3795 \programs\vim\vim74\autoload\netrw.vim
badd +1 DrawWireSelectMouseable.h
badd +1 WireSelectMouseable.cpp
badd +13 WireSelectMouseable.h
badd +0 powershell\ -\ 1
badd +0 CircuitGraph.h
badd +0 CircuitGraph.cpp
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
exe 'vert 1resize ' . ((&columns * 103 + 137) / 274)
exe '2resize ' . ((&lines * 26 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 103 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 170 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 170 + 137) / 274)
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
let s:l = 19 - ((9 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
19
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
let s:l = 6 - ((5 * winheight(0) + 13) / 26)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
6
normal! 013|
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
let s:l = 442 - ((14 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
442
normal! 05|
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
let s:l = 49 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
49
normal! 05|
lcd e:\projects\Waves\Waves
wincmd w
exe '1resize ' . ((&lines * 37 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 103 + 137) / 274)
exe '2resize ' . ((&lines * 26 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 103 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 170 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 170 + 137) / 274)
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
exe 'vert 1resize ' . ((&columns * 79 + 137) / 274)
exe '2resize ' . ((&lines * 19 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 97 + 137) / 274)
exe '3resize ' . ((&lines * 44 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 97 + 137) / 274)
exe 'vert 4resize ' . ((&columns * 96 + 137) / 274)
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
let s:l = 43 - ((42 * winheight(0) + 32) / 64)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
43
normal! 09|
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
exe 'vert 1resize ' . ((&columns * 79 + 137) / 274)
exe '2resize ' . ((&lines * 19 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 97 + 137) / 274)
exe '3resize ' . ((&lines * 44 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 97 + 137) / 274)
exe 'vert 4resize ' . ((&columns * 96 + 137) / 274)
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
exe '1resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 87 + 137) / 274)
exe '2resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 87 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 103 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 103 + 137) / 274)
exe '5resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 82 + 137) / 274)
exe '6resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 82 + 137) / 274)
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
let s:l = 74 - ((17 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
74
normal! 051|
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
let s:l = 1 - ((0 * winheight(0) + 17) / 34)
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
let s:l = 17 - ((14 * winheight(0) + 14) / 29)
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
let s:l = 19 - ((16 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
19
normal! 09|
lcd e:\projects\Waves\Waves
wincmd w
exe '1resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 87 + 137) / 274)
exe '2resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 87 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 103 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 103 + 137) / 274)
exe '5resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 82 + 137) / 274)
exe '6resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 82 + 137) / 274)
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
exe '1resize ' . ((&lines * 37 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 85 + 137) / 274)
exe '2resize ' . ((&lines * 26 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 85 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 83 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 83 + 137) / 274)
exe '5resize ' . ((&lines * 30 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 104 + 137) / 274)
exe '6resize ' . ((&lines * 33 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 104 + 137) / 274)
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
let s:l = 20 - ((15 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
20
normal! 09|
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
let s:l = 2 - ((1 * winheight(0) + 13) / 26)
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
let s:l = 82 - ((27 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
82
normal! 030|
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
let s:l = 40 - ((28 * winheight(0) + 15) / 30)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
40
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
let s:l = 30 - ((15 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
30
normal! 041|
lcd e:\projects\Waves\Waves
wincmd w
4wincmd w
exe '1resize ' . ((&lines * 37 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 85 + 137) / 274)
exe '2resize ' . ((&lines * 26 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 85 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 83 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 83 + 137) / 274)
exe '5resize ' . ((&lines * 30 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 104 + 137) / 274)
exe '6resize ' . ((&lines * 33 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 104 + 137) / 274)
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
exe '1resize ' . ((&lines * 43 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 79 + 137) / 274)
exe '2resize ' . ((&lines * 20 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 79 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 97 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 97 + 137) / 274)
exe '5resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 96 + 137) / 274)
exe '6resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 96 + 137) / 274)
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
let s:l = 57 - ((41 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
57
normal! 023|
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
let s:l = 9 - ((8 * winheight(0) + 10) / 20)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
9
normal! 030|
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
let s:l = 28 - ((27 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
28
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
let s:l = 55 - ((33 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
55
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
let s:l = 13 - ((12 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
13
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
let s:l = 8 - ((7 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
8
normal! 023|
lcd e:\projects\Waves\Waves
wincmd w
exe '1resize ' . ((&lines * 43 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 79 + 137) / 274)
exe '2resize ' . ((&lines * 20 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 79 + 137) / 274)
exe '3resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 97 + 137) / 274)
exe '4resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 97 + 137) / 274)
exe '5resize ' . ((&lines * 29 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 96 + 137) / 274)
exe '6resize ' . ((&lines * 34 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 96 + 137) / 274)
tabedit e:\projects\Waves\Waves\CircuitGraph.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 136 + 137) / 274)
exe 'vert 2resize ' . ((&columns * 137 + 137) / 274)
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
edit e:\projects\Waves\Waves\CircuitGraph.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 9 - ((8 * winheight(0) + 32) / 64)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
9
normal! 0
lcd e:\projects\Waves\Waves
wincmd w
exe 'vert 1resize ' . ((&columns * 136 + 137) / 274)
exe 'vert 2resize ' . ((&columns * 137 + 137) / 274)
tabnext 4
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
