# Usage
#  make -C <target> -f ../Makefile [pdf|handout|final]
#
#  <target> is the folder where the source code is
#
#  pdf  -> make the presentation only
#  handout -> make the handout only
#
#  final -> make the handout only and compress it
#  	    (lower their quality and using 7z)
#
#  by default, make both the presentation and the handout
#

TMP=tmp
COMPRESS_LEVEL=screen

COMPILE_FLAGS=-output-directory=${TMP} -output-format=pdf
GS_FLAGS=-sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -r150 -dPDFSETTINGS=/${COMPRESS_LEVEL} -dNOPAUSE -dQUIET -dBATCH
COMPRESS_FLAGS=-t7z -m0=lzma -mx=9 -mfb=64 -md=128m -ms=on

MAIN=$(shell basename $(CURDIR))

all: pdf handout

pdf: _prepare
	latex ${COMPILE_FLAGS} '\def\handoutmode{0}\def\pptsupportmode{0}\input{${MAIN}}'
	latex ${COMPILE_FLAGS} '\def\handoutmode{0}\def\pptsupportmode{0}\input{${MAIN}}'
	cp ${TMP}/${MAIN}.pdf ${MAIN}.pdf

ppt: _prepare
	latex ${COMPILE_FLAGS} '\def\handoutmode{0}\def\pptsupportmode{1}\input{${MAIN}}'
	latex ${COMPILE_FLAGS} '\def\handoutmode{0}\def\pptsupportmode{1}\input{${MAIN}}'
	cp ${TMP}/${MAIN}.pdf ${MAIN}-for-ppt.pdf

handout:  _prepare
	latex -output-directory=tmp -output-format=pdf '\def\handoutmode{1}\def\pptsupportmode{0}\input{${MAIN}}'
	latex -output-directory=tmp -output-format=pdf '\def\handoutmode{1}\def\pptsupportmode{0}\input{${MAIN}}'
	pdfnup ${TMP}/${MAIN}.pdf --nup 2x3 --no-landscape --paper letterpaper --frame True --suffix "handout"


final: handout 
	gs ${GS_FLAGS} -sOutputFile=${TMP}/${MAIN}-handout.${COMPRESS_LEVEL}.pdf ${MAIN}-handout.pdf
	mv ${TMP}/${MAIN}-handout.${COMPRESS_LEVEL}.pdf ${MAIN}-handout.pdf
	mat ${MAIN}-handout.pdf
	7z a ${COMPRESS_FLAGS} ${MAIN}.7z ${MAIN}-handout.pdf

clean: _check 
	rm -f ${MAIN}.7z ${MAIN}.pdf ${MAIN}-handout.pdf
	rm -Rf ${TMP}

_check:
	[ -f ${MAIN}.tex ] || ( echo "Usage make -C <target> -f ../Makefile [pdf|handout|final]" && exit 1 )

_prepare: _check
	mkdir -p ${TMP}
