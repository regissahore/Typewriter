use File::Basename;
use File::Spec;
my $symlink = $ARGV[0] eq '-s';
shift @ARGV if $symlink;
my ($src, $dst) = @ARGV;
if (-d $dst) {
    my $basename = basename $src;
    $dst = File::Spec->catfile($dst, $basename);
}
if ($symlink) {
    symlink $src, $dst;
} else {
    link $src, $dst;
}