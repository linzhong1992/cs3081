#mia executable
CMD = @../../MIA/MIA
#this is the input test image
INPUT = input.png
#this is the output
OUTPUT = output.png
#input output directory
DIR = testing_files

all: libphoto_filters

clean:
	rm -r $(DIR)/test_result
	rm -r $(DIR)/output.png

#filters implemented in libphoto
libphoto_filters: compile convolution algorithm

compile:
	(cd ../../MIA; make;)
	@echo "_____TESTING LIBPHOTO FILTERS_____";

convolution: test_blur test_edgeDetect test_sharpen

BLUR_AMOUNT = 50
test_blur:
	$(CMD) $(DIR)/$(INPUT) -blur $(BLUR_AMOUNT) $(DIR)/$(OUTPUT) > $(DIR)/test_result
	$(CMD) $(DIR)/$(OUTPUT) -compare $(DIR)/blur_result.png > $(DIR)/test_result
	@if grep -R "1" $(DIR)/test_result ; then\
		echo "*****BLUR TEST SUCCESS*****";\
	else\
		echo "*****BLUR TEST FAIL*****";\
	fi

test_edgeDetect:
	$(CMD) $(DIR)/$(INPUT) -edgedetect $(DIR)/$(OUTPUT)> $(DIR)/test_result
	$(CMD) $(DIR)/$(OUTPUT) -compare $(DIR)/edgedetect_result.png > $(DIR)/test_result
	@if grep -R "1" $(DIR)/test_result ; then\
		echo "*****EDGEDETECT TEST SUCCESS*****";\
	else\
		echo "*****EDGEDETECT TEST FAIL*****";\
	fi

SHARPEN_AMOUNT = 10
test_sharpen:
	$(CMD) $(DIR)/$(INPUT) -sharpen $(SHARPEN_AMOUNT) $(DIR)/$(OUTPUT)> $(DIR)/test_result
	$(CMD) $(DIR)/$(OUTPUT) -compare $(DIR)/sharpen_result.png > $(DIR)/test_result
	@if grep -R "1" $(DIR)/test_result ; then\
		echo "*****SHARPEN TEST SUCCESS*****";\
	else\
		echo "*****SHARPEN TEST FAIL*****";\
	fi

algorithm: test_quantize test_saturate test_threshold test_multrgb

QUANTIZE_AMOUNT = 8
test_quantize:
	$(CMD) $(DIR)/$(INPUT) -quantize $(QUANTIZE_AMOUNT) $(DIR)/$(OUTPUT)> $(DIR)/test_result
	$(CMD) $(DIR)/$(OUTPUT) -compare $(DIR)/quantize_result.png > $(DIR)/test_result
	@if grep -R "1" $(DIR)/test_result ; then\
		echo "*****QUANTIZE TEST SUCCESS*****";\
	else\
		echo "*****QUANTIZE TEST FAIL*****";\
	fi

SATURATE_AMOUNT = 0
test_saturate:
	$(CMD) $(DIR)/$(INPUT) -saturate $(SATURATE_AMOUNT) $(DIR)/$(OUTPUT)> $(DIR)/test_result
	$(CMD) $(DIR)/$(OUTPUT) -compare $(DIR)/saturate_result.png > $(DIR)/test_result
	@if grep -R "1" $(DIR)/test_result ; then\
		echo "*****SATURATION TEST SUCCESS*****";\
	else\
		echo "*****SATURATION TEST FAIL*****";\
	fi

THRESHOLD_AMOUNT = 0.5
test_threshold:
	$(CMD) $(DIR)/$(INPUT) -thresh $(THRESHOLD_AMOUNT) $(DIR)/$(OUTPUT)> $(DIR)/test_result
	$(CMD) $(DIR)/$(OUTPUT) -compare $(DIR)/thresh_result.png > $(DIR)/test_result
	@if grep -R "1" $(DIR)/test_result ; then\
		echo "*****THRESHOLD TEST SUCCESS*****";\
	else\
		echo "*****THRESHOLD TEST FAIL*****";\
	fi

RED = 1.5
GREEN = 1.2
BLUE = 0.7
test_multrgb:
	$(CMD) $(DIR)/$(INPUT) -multrgb $(RED) $(GREEN) $(BLUE) $(DIR)/$(OUTPUT)> $(DIR)/test_result
	$(CMD) $(DIR)/$(OUTPUT) -compare $(DIR)/multrgb_result.png > $(DIR)/test_result
	@if grep -R "1" $(DIR)/test_result ; then\
		echo "*****MULTRGB TEST SUCCESS*****";\
	else\
		echo "*****MULTRGB TEST FAIL*****";\
	fi
