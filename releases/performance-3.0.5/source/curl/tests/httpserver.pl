#!/usr/bin/env perl

use strict;

my $verbose=0; # set to 1 for debugging

my $port = 8999; # just a default
do {
    if($ARGV[0] eq "-v") {
        $verbose=1;
    }
    elsif($ARGV[0] =~ /^(\d+)$/) {
        $port = $1;
    }
} while(shift @ARGV);

exec("server/sws $port");
