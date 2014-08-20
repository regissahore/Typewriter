use File::Basename;
use File::Spec;
my ($src, $dst) = @ARGV;
if (-d $dst) {
    my $basename = basename $src;
    $dst = File::Spec->catfile($dst, $basename);
}
link $src, $dst;