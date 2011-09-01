""""""""""""""""""""""""""""""
" 缩进
"
""""""""""""""""""""""""""""""
set cindent 
    "按照 C 语言的语法，自动地调整缩进的长度
set expandtab    
    " 使用space代替tab
set shiftwidth=4    
    "自动缩进的宽度。
set pastetoggle=<F8>    
    "设置输入 :set paste, set nopaste快捷键
filetype plugin on    
    "开启插件




"快捷键
"<f2>
nnoremap <silent> <F2>  <C-W><C-W><CR>  
    "窗口切换快捷键F2
"<f3>
nnoremap <silent> <F3>  :A<CR>  
   "设置切换快捷键为F3
"<f4>
nnoremap <silent> <F4> :q<CR>
    "关闭当前窗口
"<f5>
nnoremap <silent> <F5> :e<CR>
    "文件更新
"<f6>
nnoremap <silent> <F6> :set nu!<CR>   
     "显示行号
"<f6>
"nnoremap <silent> <F6> :set foldenable!<CR>
    "代码折叠


"<f7>     
nmap <F7> :WMToggle<cr>
    "正常模式下按键wm可打开窗口
nnoremap <silent> <F8> <C-]><CR>
    "跳转到代码定义点

"<f9>
"系统占用
"<f10>
"系统占用
"<f12>
nnoremap <silent> <F12> :TlistToggle <CR>

nnoremap <silent> <C-f> :Grep <CR>




""""""""""""""""""""""""""""""
" Tag list    ==> 需要安装插件 taglist 和软件 ctags
"
""""""""""""""""""""""""""""""
"let Tlist_Show_One_File = 1 
    "不同时显示多个文件的tag，只显示当前文件的
"let Tlist_Exit_OnlyWindow = 1    
    "如果taglist窗口是最后一个窗口，则退出vim
let Tlist_Use_Right_Window = 1     
    "在右侧窗口中显示taglist窗口




"""""""""""""""""""""""""""""""
" 字体和颜色
"
"""""""""""""""""""""""""""""""
syntax enable    
    "开启语法
set guifont=dejaVu\ Sans\ Monospace\ 12    
    "设置字体
colorscheme desert 
    "设置配色    
set cursorline
    "高亮显示当前行
hi cursorline guibg=#222222
hi CursorColumn guibg=#333333





"""""""""""""""""""""""""""""""
" 自动补全   ==> 需要安装插件supertab
"
"""""""""""""""""""""""""""""""
let g:SuperTabRetainCompletionType=2
let g:SuperTabDefaultCompletionType="<C-X><C-O>"
    "TAB键补全




"""""""""""""""""""""""""""""""
" wmwinmanager管理   ==>需要安装插件 winmanager
"
"""""""""""""""""""""""""""""""
"let g:winManagerWindowLayout='FileExplorer|TagList'
let g:winManagerWindowLayout='FileExplorer'





"""""""""""""""""""""""""""""""
" cscope   ==>需要安装软件 cscope
"
"""""""""""""""""""""""""""""""
set cscopequickfix=s-,c-,d-,i-,t-,e-
    "设定是否使用 quickfix 窗口来显示 cscope 结果








"""""""""""""""""""""""""""""""
" 外部文件修改自动加载
"
"""""""""""""""""""""""""""""""
set autoread




"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => 文件和备份
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"关闭自动备份
set nobackup
set nowb

"关闭交换文件
set noswapfile


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""  
"可选配置    ==>根据情况自行开启
"
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""





""""""""""""""""""""""""""""""""
" 折叠
"
""""""""""""""""""""""""""""""""
"set fdl=0
"set fdc=2
"set fdm=marker
set fdm=syntax
    "开启折叠
set nofoldenable   
    "默认不折叠







set helplang=cn


"高亮显示搜索的内容
set hlsearch
