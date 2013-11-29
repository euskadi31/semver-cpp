#export LD_LIBRARY_PATH=./build:/usr/local/lib

scons:
	@scons

install:
	@scons install

test: scons
	@./build/semvar-test --log_level=error --detect_memory_leaks=1 --report_level=detailed --report_format=xml 2> ./build/xunit.xml

clean:
	@scons -c