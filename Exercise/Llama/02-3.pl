$pi = 3.141592654;
$radius = <STDIN>;
if ($radius < 0) {
    $perimeter = 0;
} else {
    $perimeter = 2 * $pi * $radius;
}
print 'Primeter: ' . $perimeter;