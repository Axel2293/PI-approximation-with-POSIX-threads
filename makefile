src_dir=src
lib_pt=-lpthread

src_files=$(wildcard $(src_dir)/*.c)

target = piaproximation

$(target): $(src_files)
	gcc $^ -o $@ $(lib_pt)
	
clean:
	rm -f $(target)
	rm -f $(bin_files)
