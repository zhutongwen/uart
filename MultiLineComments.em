//将上面的代码另存为xxx.em文件，打开source insight，将该文件添加到工程中，然后在Options->KeyAssignments中你就可以看到这个宏了，
//宏的名字是MultiLineComments，然后我们为它分配快捷键“Ctrl + /”，然后就可以了。
macro MultiLineComment()

{

    hwnd = GetCurrentWnd()

    selection = GetWndSel(hwnd)

    LnFirst =GetWndSelLnFirst(hwnd)      //取首行行号

    LnLast =GetWndSelLnLast(hwnd)      //取末行行号

    hbuf = GetCurrentBuf()

 

    if(GetBufLine(hbuf, 0) =="//magic-number:tph85666031"){

        stop

    }

 

    Ln = Lnfirst

    buf = GetBufLine(hbuf, Ln)

    len = strlen(buf)

 

    while(Ln <= Lnlast) {

        buf = GetBufLine(hbuf, Ln)  //取Ln对应的行

        if(buf ==""){                   //跳过空行

            Ln = Ln + 1

            continue

        }

 

        if(StrMid(buf, 0, 1) == "/"){       //需要取消注释,防止只有单字符的行

            if(StrMid(buf, 1, 2) == "/"){

                PutBufLine(hbuf, Ln, StrMid(buf, 2, Strlen(buf)))

            }

        }

 

        if(StrMid(buf,0,1) !="/"){          //需要添加注释

            PutBufLine(hbuf, Ln, Cat("//", buf))

        }

        Ln = Ln + 1

    }

 

    SetWndSel(hwnd, selection)

}
