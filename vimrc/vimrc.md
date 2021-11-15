vim用法

[视频教程](https://www.bilibili.com/video/BV1e4411V7AA/?spm_id_from=autoNext)

[vimrc github模板](https://github.com:theniceboy/.vim)



# 概念：

`<operation> <motion>` （“操作-动作”）

比如删除当前光标所指位置开始的3个字符。

`x`,`s`,

`d3→`: `d`就是`<operation>`，`3→`就是`<motion>`

视频时间：33:27

# Operation

`y`：复制。



| <operation> | operation含义                          | <motion>        | motion含义                                                   |
| ----------- | -------------------------------------- | --------------- | ------------------------------------------------------------ |
| i           | insert，光标前面插入                   |                 |                                                              |
| I           | Insert，行首插入                       |                 |                                                              |
| a           | append，光标后面插入                   |                 |                                                              |
| o           | 下一新行插入                           |                 |                                                              |
| O           | 上一新行插入                           |                 |                                                              |
| A           | Append，行尾插入                       |                 |                                                              |
| x           | 删除光标当前字符                       |                 |                                                              |
| s           | 删除当前字符，并且进入insert模式       |                 |                                                              |
| d           | 删除（实际上vim只有剪切的概念）        | 3→，d           | 向右3个字符。dd，重复按一个d表示删除当前行。                 |
| y           | 复制                                   | w，b            | word，选择1个单词。不断按w键，可以按照单词跳转。back，表示上1个单词。 |
| c           | change，改变当前字符（类似于覆写模式） | w，iw，i"，3→等 | word，选择当前单词。in word，如果光标在词中，ciw可以改变当前单词。ci"表示改变引号中的字符串。 |
|             |                                        | find：fv，dfv   | fv表示定位到字符v的位置。dfv表示从当前位置一直删除到v字符。  |
| r           | replace，替换当前字符                  |                 |                                                              |



### 宏录制

普通模式下，`q + 任意键`，进入record模式

在非insert模式下，再次按下`q`，退出record模式。



### 搜索

`/`：



### 命令

`:x` ：与`ZZ`（大写字母）相同，保存文件并退出。

":x" 和 ":wq" 的区别如下：
(1) :wq 强制性写入文件并退出（存盘并退出 write and quite）。即使文件没有被修改也强制写入，并更新文件的修改时间。
(2) :x 写入文件并退出。仅当文件被修改时才写入，并更新文件修改时间；否则不会更新文件修改时间。
这两者一般情况下没什么不一样，但是在编程方面，对编辑源文件可能会产生重要影响。因为文件即使没有修改，":wq" 强制更新文件的修改时间，
这样会让 make 编译整个项目时以为文件被修改过了，然后就得重新编译链接生成可执行文件。这可能会产生让人误解的后果，当然也产生了不必要的系统资源花销。不过像是版本控制的软件一般首选还是比较文件内容，修改时间一般不加以理会。

`zz`：小写，把当前行显示在屏幕中间。

leader键，即快捷键的前缀。



# vim配置

```bash
mkdir -p ~/.vim/{doc,plugin,syntax}
cd ~/.vim/
touch vimrc
```

**vimrc模板及说明：**

```bash
"插件兼容
set nocompatible
"让vim能识别不同插件的文件格式
filetype on
filetype indent on
filetype plugin on
filetype plugin indent on
"让vim能够使用鼠标
set mouse=a
"让不同终端能自适应vim配色，使得显示正常
let &t_ut=''
"tab转空格
"可以用:h set查看options
set expandtab
"tab缩进
set tabstop=2
set shiftwidth=2
set softtabstop=2
"显示行尾的空格
set list
"set listchars=tab:

"在行首按下退格键能够退到上一行的行尾
set backspace=indent,eol,start
"代码折叠
set foldmethod=indent
set foldlevel=99

"让光标在vim不同模式下的形状不一样
"这里的t应该表示的是terminal终端
let &t_SI = "\<Esc>]50;CursorShape=1\x7"

"让底下的状态栏永远是2
set laststatus=2
"让vim执行命令时，切换到当前目录
set autochdir
```



# vim安装插件

## 插件管理器

github搜索vim-plug，这是一个韩国人写的vim插件管理器。

### 下载并且安装vim-plug

```bash
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

如果上面的网址"https://raw.githubusercontent.com"无法访问，直接将github上下载的vim-plug仓库里的plug.vim复制到autoload目录也行。

## 安装插件（利用vim-plug插件管理器）

在~/.vim/vimrc中写入如下内容：

```bash
call plug#begin('~/.vim/plugged')

"安装插件airline，这个插件在github上可以搜到
"Plug的单引号中是插件在github.com的URL文件路径
" vim模式显示插件
Plug 'vim-airline/vim-airline'
" 配色方案插件
Plug 'connorholyday/vim-snazzy'

call plug#end()
```

保存退出。重新进入vim，普通模式下`:PlugInstall`并且按下tab，vim-plug就会自动帮我们安装这些插件。安装完成之后，按`q`退出插件安装模式。



#### 常用插件

| 插件名                       | 功能                                               | 安装方法                                                     |
| ---------------------------- | -------------------------------------------------- | ------------------------------------------------------------ |
| scrooloose/nerdtree          | 文件树功能                                         |                                                              |
| ycm-core/YouCompleteMe       | 代码补全，支持所有语言                             | 需要手动安装。cd plugged/YouCompleteMe，sudo python3 install.py会安装。 |
| w0rp/ale   dense-analysis/ale                    | 实时代码语法检查                                   |                                                              |
| preservim/tagbar             | 在vim右边显示函数列表                              |                                                              |
| mbbill/undotree              | 浏览文件修改历史，树状图展示，可以在历史版本中切换 |                                                              |
| iamcco/markdown-preview.nvim | 实时预览markdown                                   |                                                              |



### 配色

`:color + 空格 + tab`：可以选择配色



# 模式

## 可视模式

- `v`：在普通模式下按下`v`，进入visual模式。

- `shift` + `v`：Visual Line，可视行模式。

- `ctrl` +` v`：Visual Block，可视块模式，也就是列模式。

  `:normal`+`空格`+`普通模式下的操作`：

  - 在可视模式下，选中一些区域，按下`:`，并且输入`normal` + `空格`，接下来的操作，将普通模式下的所有改变应用到所有选中区域。

  - 输入`A (<++>)`，在选中区每行末尾输入`(<++>)`，`<++>`是自定义的placeholder。

    ```bash
    # vimrc
    "先按Esc退出，然后查找<++>，回车，将查找时高亮关闭，回车，然后向右替换4个字符（即'<++>'）
    map <LEADER><LEADER> <Esc>/<++><CR>:nohlsearch<CR>c4l
    ```

    

在visual模式下，按`G`会从当前位置一直选中到最后一行。

选中区域之后，可以执行普通模式下的其他操作，例如`I`、`A`、`c`、`d`等，其中`I`、`A`、`c`这些操作（注意：只有大写的`I`和`A`有效，并且这里的`I`和`A`将修改分别当前字符的前面和后面，而不是行首和行尾）改动完成之后，按下`Esc`退出insert模式，再次按下`Esc`退出visual模式，此时会将所有改动应用到所有选中区域。







#### 分屏

`:split`上下分屏

`:vsplit`左右分屏，光标默认放在左屏。如果先执行`:set splitright`，再执行`:vsplit`，那么分屏之后光标放在右边。

分屏间跳转：`ctrl`+`w`，然后按`hjkl`在各分屏间跳转。

`:res`：更改上下分屏大小，例如`:res 10`，当前屏幕显示为10行。`:res +5`当前屏幕增加5行。

`:vertical resize-5`：左右分屏大小更改。`resize-5`将当前分屏的列宽减少5列。

 **分屏切换位置：** 

`ctrl`+`w`+`t`+`ctrl`+`w`+`H`：将原来的垂直分屏改成左右分屏。

`ctrl`+`w`+`t`+`ctrl`+`w`+`K`：将原来的左右分屏改成上下分屏。

#### 标签页

`:tabe`：打开新的标签页
`:-tabnext`：跳转到下一个标签页，`-`表示向左跳转，`+`表示向右跳转。
`:tabp`：跳转到前一个标签页。
`:tabn`：跳转到后一个标签页。


## vimrc的键码

`:help keycodes`

`:help <C-`：查看`<C-`表示的键。

`<CR>`：在vimrc表示Enter。

## 杂项

`:r !cat a.txt`：将a.txt的内容添加到当前文档中。

`:!`：`:!`之后可以执行shell命令，例如`:! ls -l`。

`:w 文件名（可以包含路径）`：文件另存为其他位置。

`:w !sudo tee %`：如果当前目录没有权限，不能写入文件，那么可以执行这条命令，然后`:q!`强制退出。这样可以获取root权限并且保存文件。`!`表示执行shell命令，`%`表示当前文件名。man page说明：

> :[range]w[rite] !{cmd}  Execute {cmd} with [range] lines as standard input
>
> (note the space in front of the ‘!’).  {cmd} is executed like with “:!{cmd}”, any ‘!’ is replaced with the previous command



#### `figlet`小工具

Linux有个工具叫做`figlet`，可以将字符写成一张ascii表示的图。

```bash
# 安装figlet
$ sudo apt-get install figlet
# 把"ABC"生成图
$ figlet ABC
    _    ____   ____ 
   / \  | __ ) / ___|
  / _ \ |  _ \| |    
 / ___ \| |_) | |___ 
/_/   \_\____/ \____|
                     
```

#### 当前文件转成html

`:%TOhtml`：`%`表示当前文件。

#### 数字自动加减

`Ctrl`+`a`：光标定位到数字上，按下这两个键，将当前数字加1。

`Ctrl`+`x`：光标定位到数字上，按下这两个键，将当前数字减1。

#### 拼写检查

`:set spell`：开启拼写检查。`]s`下一个拼写错误，`[s`上一个拼写错误。

`:set spell!`：表示关闭拼写检查，这里`!`表示关闭。

在拼写错误位置，按下`z=`，可以显示拼写建议。

开启拼写检查，在写入模式下，如果想查询写到一半的单词怎么写，可以按下`Ctrl`+`x`+`s`，会弹出拼写建议，然后按`Ctrl`+`N`或`Ctrl`+`P`选择，如果输入下一个字符，则认为当前的拼写建议被采纳。



#### 位置跳转

`Ctrl`+`o`：后退到上一个编辑位置。可以跨文件。

`Ctrl`+`i`：前进到上一个编辑位置。可以跨文件。



## 帮助文档

`:help xxx`或`:h xxx`：查询帮助文档。

`:set`：不输入其他命令，直接按下`Enter`，就会显示能够设置的`options`。`:h set`可以查看`options`的说明。