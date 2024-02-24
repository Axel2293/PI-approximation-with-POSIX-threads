bin_dir=bin
src_dir=src

src_files=$(wildcard $(src_dir)/*.c)
bin_files=$(patsubst $(src_dir)/%.c, $(bin_dir)/%.o, $(src_files))

target = piaproximation

$(target): $(src_files)
	gcc $^ -o $@


clean:
	rm -f $(target)
	rm -f $(bin_files)
