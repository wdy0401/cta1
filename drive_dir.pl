use File::Basename;
use Getopt::Long;
use strict;
use 5.010;
my $dir="";
my $cmd="";
my $debug=0;
GetOptions(
	"dir=s" =>\$dir,
	"cmd=s" => \$cmd,
	"debug=s" => \$debug,
);

&parsedir($dir);
sub parsedir(@_)
{
	my $dir=shift @_;
	if (-d $dir)
	{
		opendir DH ,$dir;
		for my $file(readdir DH)
		{
			next if $file=~/^\.{1,2}$/;
			&parsedir("$dir/$file");
		}
	}
	else
	{
		my $file=$dir;
		next unless $file =~/(simu_dll|\.)\/\S+\/\S+.h$/;
		next if $file=~/datafeed/;
		
		my $runcmd="perl ./fix_h.pl -file $file";

		if($debug)
		{
			print "$runcmd\n";
			
		}
		else
		{
			print "Runing $runcmd\n";
			system( "$runcmd");
		}		
	}
}