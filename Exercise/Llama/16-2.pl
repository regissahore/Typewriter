open STDOUT, '>', 'ls.out';
open STDERR, '>', 'ls.err';
chdir '/';
exec 'ls', '-l';