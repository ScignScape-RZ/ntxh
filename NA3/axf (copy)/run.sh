ar=`git rev-parse --show-toplevel`
`cat $ar/../preferred-pdflatex` -synctex=1 -interaction=nonstopmode --shell-escape axf-platform.tex
