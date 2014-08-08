$fileName = "vp_ego.adjacency.txt";

open FILE, "<", $fileName or die "Could not find file\n";

$hashCounter = {};
$hashBoss    = {};

$counter = 0;
@vps     = ();

while (<FILE>) {

	$counter++;
	chomp $_;

	@categories = split( ' ', $_ );

	#print "Reading $_\n";

	$boss     = $categories[0];
	$employee = $categories[1];

	if ( $boss != 0 && $employee != 0 ) {

		if ( exists $hashBoss{$employee} ) {
			die "Employee already encountered\n";
		}

		else {

			if ( $boss == 1 ) {
				push( @vps, $employee );
			}

			$hashBoss{$employee} = $boss;
			if ( exists $hashCounter{$boss} ) {

				$hashCounter{$boss}++;

			}

			else {

				$hashCounter{$boss} = 1;
			}

		}

	}

}

foreach(@vps){
	print "Number of employees of vp $_ are: $hashCounter{$_}\n";
}

for my $key ( keys %hashCounter ) {
	
	$node=$key;

	if ( $hashBoss{$node} != 1 && $node != 1 )
	{

		while ( $hashBoss{$node} != 1 ) {
			$node = $hashBoss{$node};
		}

		$hashCounter{$node} += $hashCounter{$key};
	}
	
}

$min         = $counter;
$leastValued = -1;

foreach (@vps) {

	$key   = $_;
	$value = $hashCounter{$key};

	if ( $value < $min ) {
		$min         = $value;
		$leastValued = $key;
	}

}

print "Least important VP is: $leastValued with $min employees\n";
