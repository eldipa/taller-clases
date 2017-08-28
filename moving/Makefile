# Usage
#  make pdf  -> make the presentation only
#  make handout -> make the handout only
#
#  make  -> make both the presentation and the handout
#
#  make final -> make the handout only and compress it
#  		 (lower their quality and using 7z)
#
MAIN=moving

TMP=tmp
COMPRESS_LEVEL=screen

COMPILE_FLAGS=-output-directory=${TMP} -output-format=pdf
GS_FLAGS=-sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -r150 -dPDFSETTINGS=/${COMPRESS_LEVEL} -dNOPAUSE -dQUIET -dBATCH
COMPRESS_FLAGS=-t7z -m0=lzma -mx=9 -mfb=64 -md=128m -ms=on


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


final: handout
	gs ${GS_FLAGS} -sOutputFile=${TMP}/${MAIN}-handout.${COMPRESS_LEVEL}.pdf ${MAIN}-handout.pdf
	mv ${TMP}/${MAIN}-handout.${COMPRESS_LEVEL}.pdf ${MAIN}-handout.pdf
	mat ${MAIN}-handout.pdf
	7z a ${COMPRESS_FLAGS} ${MAIN}.7z ${MAIN}-handout.pdf

clean:
	rm -f ${MAIN}.7z ${MAIN}.pdf ${MAIN}-handout.pdf
	rm -Rf ${TMP}

