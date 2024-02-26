lib_pt=-lpthread

src_files=singlethread.c

target = piaproximation_singlethread

$(target): $(src_files)
	gcc $^ -o $@ $(lib_pt)

clean:
	rm -f $(target)
