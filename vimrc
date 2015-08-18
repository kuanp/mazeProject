" runtime! debian.vim

 " execute pathogen#infect()
 colorscheme desert
 "filetype on
 "set nocompatible
 "filetype off

 "set rtp+=~/.vim/bundle/vundle/
 "call vundle#rc()

 "Bundle 'gmarik/vundle'
 "filetype plugin indent on

 syntax on
 "au Syntax py runtime! syntax/python.vim
 set background=dark
 "colorscheme blackboard
 "colorscheme solarized

 let c_no_curly_error=1
 set foldmethod=syntax
 nnoremap <space> za
 set incsearch
 nnoremap ^ 0
 set ignorecase
 set smartcase
 set scrolloff=3
 set cindent
 set autoindent
 set showcmd
 set showmatch
 set mouse=a
 "set columns=80
 "set textwidth=79
 "set wm=2

 set tabstop=8
 set shiftwidth=4
 set softtabstop=4
 set expandtab
 set number
 set ai
 filetype plugin indent on
 autocmd BufEnter * :syntax sync minlines=200

 set ruler
 set visualbell
 set noendofline binary

 autocmd Syntax * syn match Error /\s\+$\| \+\ze\t/ containedin=ALL display
 au BufReadPost * if line("'\"") > 0|if line("'\"") <= line("$")|exe("norm '\"")|else|exe "no    rm $"|endif|endif

 command CleanUpWhiteSpace  %s/ \+$//
 highlight ExtraWhitespace ctermbg=red guibg=red
 match ExtraWhitespace /\s\+$/
 autocmd BufWinEnter * match ExtraWhitespace /\s\+$/
 autocmd InsertEnter * match ExtraWhitespace /\s\+\%#\@<!$/
 autocmd InsertLeave * match ExtraWhitespace /\s\+$/
 autocmd BufWinLeave * call clearmatches()
