# Usage
#  make -C <target> -f ../Makefile [pdf|handout|interactive|all]
#
#  <target> is the folder where the source code is
#
#  pdf  -> make the presentation only
#  handout -> make the handout only,  lower their quality and compress it (7z)
#  interactive -> make the presentation for interactive hand-writing videos
#
#  all -> make all the targets
#
# If the <target> contains multiple .tex files, all of them will be
# processed.
# If only a subset is wanted, define them in the  TEXFILES env variable
# (space separated list)
#
# TEXFILES=<files> make -C <target> -f ../Makefile [pdf|handout|interactive|all]
#

TMP=tmp
COMPRESS_LEVEL=ebook

COMPILE_FLAGS=-output-directory=${TMP} -output-format=pdf
GS_FLAGS=-sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -r150 -dPDFSETTINGS=/${COMPRESS_LEVEL} -dNOPAUSE -dQUIET -dBATCH
COMPRESS_FLAGS=-t7z -m0=lzma -mx=9 -mfb=64 -md=128m -ms=on
PDFJAM_FLAGS=--nup 2x3 --no-landscape --paper letterpaper --frame True

MAIN=$(shell basename $(CURDIR))

USAGE=Usage: [TEXFILES=<files>] make -C <target> -f ../Makefile [pdf|handout|interactive|all]

default:
	@echo "${USAGE}"


all: pdf handout interactive

pdf: _prepare
	set -e; if :; then			\
	    export interactive=no;  		\
	    export handout=no;        		\
	    env | j2 --customize ../j2custom.py -o ../preamble-tmp.tex ../preamble.tex; \
	    for ftex in $${TEXFILES:-*.tex}; do			\
		echo "==> $$ftex";			\
		sleep 0.5;				\
	        export iname=`basename $$ftex .tex`;	\
	        env | j2 --customize ../j2custom.py -o $$iname-tmp.tex $$iname.tex;	\
	        latex ${COMPILE_FLAGS} '\input{$$iname-tmp}';	\
	        latex ${COMPILE_FLAGS} '\input{$$iname-tmp}';	\
	        rm $$iname-tmp.tex;				\
	        mv ${TMP}/$$iname-tmp.pdf $$iname.pdf;		\
	    done;					\
	    rm ../preamble-tmp.tex;			\
	fi

handout:  _prepare
	set -e; if :; then			\
	    export interactive=no;  		\
	    export handout=yes;        		\
	    env | j2 --customize ../j2custom.py -o ../preamble-tmp.tex ../preamble.tex; \
	    for ftex in $${TEXFILES:-*.tex}; do			\
		echo "==> $$ftex";			\
		sleep 0.5;				\
	        export iname=`basename $$ftex .tex`;	\
	        env | j2 --customize ../j2custom.py -o $$iname-tmp.tex $$iname.tex;	\
	        latex ${COMPILE_FLAGS} '\input{$$iname-tmp}';	\
	        latex ${COMPILE_FLAGS} '\input{$$iname-tmp}';	\
	        rm $$iname-tmp.tex;				\
	        pdfjam ${TMP}/$$iname-tmp.pdf ${PDFJAM_FLAGS} --suffix "handout";		\
	        gs ${GS_FLAGS} -sOutputFile=${TMP}/$$iname-tmp-handout.${COMPRESS_LEVEL}.pdf $$iname-tmp-handout.pdf;	\
	        rm $$iname-tmp-handout.pdf;		\
	        mv ${TMP}/$$iname-tmp-handout.${COMPRESS_LEVEL}.pdf $$iname-handout.pdf;	\
	        7z a ${COMPRESS_FLAGS} $$iname-handout.7z $$iname-handout.pdf;	\
	    done;					\
	    rm ../preamble-tmp.tex;			\
	fi

interactive:  _prepare
	set -e; if :; then			\
	    export interactive=yes;  		\
	    export handout=no;        		\
	    env | j2 --customize ../j2custom.py -o ../preamble-tmp.tex ../preamble.tex; \
	    for ftex in $${TEXFILES:-*.tex}; do			\
		echo "==> $$ftex";			\
		sleep 0.5;				\
	        export iname=`basename $$ftex .tex`;	\
	        env | j2 --customize ../j2custom.py -o $$iname-tmp.tex $$iname.tex;	\
	        latex ${COMPILE_FLAGS} '\input{$$iname-tmp}';	\
	        latex ${COMPILE_FLAGS} '\input{$$iname-tmp}';	\
	        rm $$iname-tmp.tex;				\
	        mv ${TMP}/$$iname-tmp.pdf $$iname-interactive.pdf; \
	    done;					\
	    rm ../preamble-tmp.tex;			\
	fi

clean: _check
	rm -f *.7z *.pdf *.pptx *-tmp.* *.log
	rm -Rf ${TMP}

_check:
	# pip install j2cli
	j2 --version

_prepare: _check
	mkdir -p ${TMP}
	rm -Rf ${TMP}/*
	rm -f *-tmp.tex *-tmp.pdf
