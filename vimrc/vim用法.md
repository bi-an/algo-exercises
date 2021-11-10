vim用法

[视频教程](https://www.bilibili.com/video/BV1e4411V7AA/?spm_id_from=autoNext)



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

### 配色

`:color + 空格 + tab`：可以选择配色



# 模式

## 可视模式

- `v`：在普通模式下按下`v`，进入visual模式。

- `shift` + `v`：Visual Line，可视行模式。
- `ctrl` +` v`：Visual Block，可视块模式，也就是列模式。

在可视模式下，选中一些区域，按下`:`，并且输入`normal` + `空格`，接下来的操作，将普通模式下的所有改变应用到所有选中区域。

在visual模式下，按`G`会选中到最后一行。

选中区域之后，可以执行普通模式下的其他操作，例如`i`、`c`、`d`等，其中`i`、`c`这些操作改动完成之后，按下`Esc`，会将所有改动应用到所有选中区域。



#### 分屏

`:split`上下分屏

`:vsplit`左右分屏，光标默认放在左屏。如果先执行`:set splitright`，再执行`:vsplit`，那么分屏之后光标放在右边。

