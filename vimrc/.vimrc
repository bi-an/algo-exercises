"let: for assigning a value to a variable 
"定义快捷键的前缀，即<Leader>
"前缀键默认为"\"，这里定义为空格
let mapleader=" "

"动作映射
"noremap e i "no remap，把键盘的e键映射为i键
"noremap U 5k "按下大写U则回退5行，这样便于浏览时翻页
noremap <LEADER><CR> :nohlsearch<CR> "<Leader>键+回车，表示不要高亮

"键-命令映射
map Q :q<CR> "<CR>表示回车
map R :source $MYVIMRC<CR>
map S :w<CR>
"map s <nop> "让s键失效

"分屏设置
map <LEADER>sl :set splitright<CR>:vsplit<CR> "往右边分屏
map <LEADER>sh :set nosplitright<CR>:vsplit<CR>
map <LEADER>sk :set nosplitbelow<CR>:split<CR>
map <LEADER>sj :set splitbelow<CR>:split<CR>

" Resize splits with arrow keys
map <LEADER><up> :res +5<CR>
map <LEADER><down> :res -5<CR>
map <LEADER><left> :vertical resize-5<CR>
map <LEADER><right> :vertical resize+5<CR>

"set options
set cursorline
"no前缀 与 不加no前缀 表示的含义相反
set norelativenumber
set number "显示行号
set showcmd
set wildmenu
set wrap "显示时自动换行
set hlsearch "highlight	search
"防止每次打开新文件，还会显示上一次搜索结果
"exec的引号中表示的是vim中输入':'之后的命令
"exec表示每次打开文件时，必定执行的第一个命令
exec "nohlsearch"
set incsearch "搜索时，边输入边高亮
set ignorecase "搜索时，忽略大小写
set smartcase "搜索时，智能大小写

set autoread " reload files when changed on disk, i.e. via `git checkout`

" ===
" === Editor behavior
" ===
" Better tab
set expandtab
set tabstop=2
set shiftwidth=2
set softtabstop=2
set list
set listchars=tab:▸\ ,trail:▫
set scrolloff=5

" Copy to system clipboard
vnoremap Y :w !xclip -i -sel c<CR>

syntax on "语法高亮

call plug#begin('~/.vim/plugged')

Plug 'vim-airline/vim-airline'
"Plug 'connorholyday/vim-snazzy'

call plug#end()
