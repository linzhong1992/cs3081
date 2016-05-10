#mia executable
CMD = @../../MIA/MIA
INPUT = input.png
OUTPUT = output.png

all: compile valid invalid

compile:
	(cd ../../MIA; make;)
	@echo "_____TESTING MIA PARSER_____";

clean:
	rm output.txt
	rm output.png

valid: help sharpen edgedetect blur saturate thresh quantize multrgb
invalid: ihelp isharpen iedgedetect iblur isaturate ithresh iquantize imultrgb

help:
	@echo "*****VALID INPUTS*****"
	$(CMD) -h >> output.txt ; if [ $$? -eq 0 ] ; then echo "VALID PARSE -h SUCCESS" ; fi

sharpen:
	$(CMD) $(INPUT) -sharpen 10 $(OUTPUT) >> output.txt ; if [ $$? -eq 0 ] ; then echo "VALID PARSE -sharpen SUCCESS" ; fi

edgedetect:
	$(CMD) $(INPUT) -edgedetect $(OUTPUT) >> output.txt; if [ $$? -eq 0 ] ; then echo "VALID PARSE -edgedetect SUCCESS" ; fi

blur:
	$(CMD) $(INPUT) -blur 50 $(OUTPUT) >> output.txt; if [ $$? -eq 0 ] ; then echo "VALID PARSE -blur SUCCESS" ; fi

saturate:
	$(CMD) $(INPUT) -saturate 0 $(OUTPUT) >> output.txt; if [ $$? -eq 0 ] ; then echo "VALID PARSE -saturate SUCCESS" ; fi

thresh:
	$(CMD) $(INPUT) -thresh .5 $(OUTPUT) >> output.txt; if [ $$? -eq 0 ] ; then echo "VALID PARSE -thresh SUCCESS" ; fi

quantize:
	$(CMD) $(INPUT) -quantize 8 $(OUTPUT) >> output.txt; if [ $$? -eq 0 ] ; then echo "VALID PARSE -quantize SUCCESS" ; fi

multrgb:
	$(CMD) $(INPUT) -multrgb 1.7 1.5 .7 $(OUTPUT) >> output.txt; if [ $$? -eq 0 ] ; then echo "VALID PARSE -multrgb SUCCESS" ; fi

ihelp:
	@echo "*****INVALID INPUTS*****"
	$(CMD) -hell >> output.txt ; if [ $$? -eq 1 ] ; then echo "INVALID PARSE -h SUCCESS" ; fi

isharpen:
	$(CMD) $(INPUT) -sharpen $(OUTPUT) >> output.txt ; if [ $$? -eq 1 ] ; then echo "INVALID PARSE -sharpen SUCCESS" ; fi

iedgedetect:
	$(CMD) $(INPUT) -edgedetect 5 $(OUTPUT) >> output.txt; if [ $$? -eq 1 ] ; then echo "INVALID PARSE -edgedetect SUCCESS" ; fi

iblur:
	$(CMD) $(INPUT) -blur $(OUTPUT) >> output.txt; if [ $$? -eq 1 ] ; then echo "INVALID PARSE -blur SUCCESS" ; fi

isaturate:
	$(CMD) $(INPUT) -saturate 0 5 $(OUTPUT) >> output.txt; if [ $$? -eq 1 ] ; then echo "INVALID PARSE -saturate SUCCESS" ; fi

ithresh:
	$(CMD) $(INPUT) -thresh .5 6 $(OUTPUT) >> output.txt; if [ $$? -eq 1 ] ; then echo "INVALID PARSE -thresh SUCCESS" ; fi

iquantize:
	$(CMD) $(INPUT) -quantize 8 6 6 $(OUTPUT) >> output.txt; if [ $$? -eq 1 ] ; then echo "INVALID PARSE -quantize SUCCESS" ; fi

imultrgb:
	$(CMD) $(INPUT) -multrgb 1.7 1.5 .7 .5 $(OUTPUT) >> output.txt; if [ $$? -eq 1 ] ; then echo "INVALID PARSE -multrgb SUCCESS" ; fi
