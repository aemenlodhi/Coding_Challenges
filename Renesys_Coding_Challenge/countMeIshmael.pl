
$fileName = "mobyDick.txt";

open FILE, "<", $fileName or die "Couldn't open file $fileName\n";

$skip = 29;
$counter=0;

$hashChosen   = {};
$hashRejected = {};

while (<FILE>) {
	next if 1 .. $skip == $.;
	
	$counter++;
	next if ($counter>21746);	

	chomp $_;
	s/\p{Punct}//g;
	s/(?:\n|\s+)/ /g;

	@tokens = split /\s+/, $_;

	foreach $token (@tokens) {
		
		if ( length($token) >= 4 ) {

			$token=lc($token);

			#print "Recieved token $token\n";

			if ( exists $hashChosen{$token} ) {
				
				#print "Chosen string: $token\n";
				$hashChosen{$token}++;
			}

			elsif ( exists $hashRejected{$token} ) {

			}

			elsif ( checkString($token) == 1 ) {
				$hashChosen{$token} = 1;
				#print "Chosen string: $token\n";
			}

			else {
				$hashRejected{$token} = 1;
			}

		}

	}
	
}
	
	$counter=0;
	$rank=0;
	foreach my $word (sort { $hashChosen{$b} <=> $hashChosen{$a} or $a cmp $b } keys %hashChosen) {

		
		$counter++;	
		
		
		if($word eq "queequeg" || $word eq "ishmael"){
			$rank+=$counter;
			
			#print "$rank\t$word\t$hashChosen{$word}\n";
		
		}
		
	}
	
	print "Rank of the required question is: $rank\n";


sub checkString {

	$state = 0;

	#print "Checking string $_[0]\n";

	foreach $char ( split //, $_[0]) {
		
		#print "Character being examined $char\n";
		
		if($state==0){
			
			if(isVowel($char)==1){
				$state=0;	
			}
			
			else{
				$state=1;
			}
		}
		
		elsif($state==1){
			
			if(isVowel($char)==1){
				$state=2;
			}
			
			else{
				$state=1;
			}
				
		}
		
		elsif($state==2){
			if(isVowel($char)==1){
				$state=3;
			}	
			
			else{
				$state=1;	
			}
			
		}
		
		elsif($state==3){
			if(isVowel($char)==1){
				$state=0;
				
			}
			
			
			else{
				$state=4;
				$state=5;
				last;	
			}	
		}
		
		else{
			last;
		}
		
	}
	
	if($state==5){
		
		#print "String matching criterion found $_[0]\n";
		return 1;	
	}
	
	else{
		return 0;	
	}
}

sub isVowel {

	if (   $_[0] eq 'a'
		|| $_[0] eq 'e'
		|| $_[0] eq 'i'
		|| $_[0] eq 'o'
		|| $_[0] eq 'u'
		|| $_[0] eq 'A'
		|| $_[0] eq 'E'
		|| $_[0] eq 'I'
		|| $_[0] eq 'O'

		|| $_[0] eq 'U' )
	{
		
		#print "Vowel found $_[0]\n";
		return 1;
	}

	else {
		return 0;
	}

}