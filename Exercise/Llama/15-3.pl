use 5.010;
for (@ARGV) {
    when (! -e) {say "File does not exist.";}
    when (-r _) {say "Readable."; continue;}
    when (-w _) {say "Writable."; continue;}
    when (-x _) {say "Executable.";}
}