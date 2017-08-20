# Usage
#  make pdf  -> make the presentation only
#  make handout -> make the handout only
#
#  make  -> make both the presentation and the handout
#
#  make final -> make both the presentation and the handout then, 
#  		 compress them (lower their quality and using 7z)
#
MAIN=memoria

TMP=tmp
COMPRESS_LEVEL=screen

COMPILE_FLAGS=-output-directory=${TMP} -output-format=pdf
COMPRESS_FLAGS=-sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/${COMPRESS_LEVEL} -dNOPAUSE -dQUIET -dBATCH 

all: pdf handout

pdf: 
	mkdir -p ${TMP}
	latex ${COMPILE_FLAGS} '\def\handoutmode{0}\input{${MAIN}}'
	latex ${COMPILE_FLAGS} '\def\handoutmode{0}\input{${MAIN}}'
	cp ${TMP}/${MAIN}.pdf ${MAIN}.pdf

handout: 
	mkdir -p ${TMP}
	latex -output-directory=tmp -output-format=pdf '\def\handoutmode{1}\input{${MAIN}}'
	latex -output-directory=tmp -output-format=pdf '\def\handoutmode{1}\input{${MAIN}}'
	pdfnup ${TMP}/${MAIN}.pdf --nup 2x3 --no-landscape --paper letterpaper --frame True --suffix "handout"


final: all
	gs ${COMPRESS_FLAGS} -sOutputFile=${TMP}/${MAIN}.${COMPRESS_LEVEL}.pdf ${MAIN}.pdf
	gs ${COMPRESS_FLAGS} -sOutputFile=${TMP}/${MAIN}-handout.${COMPRESS_LEVEL}.pdf ${MAIN}-handout.pdf
	mv ${TMP}/${MAIN}.${COMPRESS_LEVEL}.pdf ${MAIN}.pdf
	mv ${TMP}/${MAIN}-handout.${COMPRESS_LEVEL}.pdf ${MAIN}-handout.pdf
	mat ${MAIN}.pdf
	mat ${MAIN}-handout.pdf
	7z a -mx=9 ${MAIN}.7z ${MAIN}.pdf ${MAIN}-handout.pdf

clean:
	rm -f ${MAIN}.7z ${MAIN}.pdf ${MAIN}-handout.pdf
	rm -Rf ${TMP}/*
	rmdir ${TMP}

