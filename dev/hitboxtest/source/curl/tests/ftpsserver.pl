#!/usr/bin/perl
#
# $Id: ftpsserver.pl,v 1.4 2003/01/21 10:29:06 bagder Exp $
# This is the FTPS server designed for the curl test suite.
#
# It is actually just a layer that runs stunnel properly.

use strict;

use stunnel;

my $stunnel = &checkstunnel;

if(!$stunnel) {
    exit;
}

#
# -p pemfile
# -P pid dir
# -d listen port
# -r target port

my $verbose=0; # set to 1 for debugging

my $port = 8821;		# just our default, weird enough
my $remote_port = 8921;		# test ftp-server port

my $path = `pwd`;
chomp $path;

my $srcdir=$path;

do {
    if($ARGV[0] eq "-v") {
        $verbose=1;
    }
    elsif($ARGV[0] eq "-r") {
        $remote_port=$ARGV[1];
        shift @ARGV;
    }
    elsif($ARGV[0] eq "-d") {
        $srcdir=$ARGV[1];
        shift @ARGV;
    }
    elsif($ARGV[0] =~ /^(\d+)$/) {
        $port = $1;
    }
} while(shift @ARGV);

my $conffile="$path/stunnel.conf";	# stunnel configuration data
my $certfile="$srcdir/stunnel.pem";	# stunnel server certificate
my $pidfile="$path/.ftps.pid";		# stunnel process pid file

open(CONF, ">$conffile") || return 1;
print CONF "
	CApath=$path
	cert = $certfile
	pid = $pidfile
	debug = 0
	output = /dev/null
	foreground = yes

	
	[curltest]
	accept = $port
	connect = $remote_port
";
close CONF; 
#system("chmod go-rwx $conffile $certfile");	# secure permissions

		# works only with stunnel versions < 4.00
my $cmd="$stunnel -p $certfile -P $pidfile -d $port -r $remote_port 2>/dev/null";

# use some heuristics to determine stunnel version
my $version_ge_4=system("$stunnel -V 2>&1|grep '^stunnel.* on '>/dev/null 2>&1");
		# works only with stunnel versions >= 4.00
if ($version_ge_4) { $cmd="$stunnel $conffile"; }

if($verbose) {
    print "FTPS server: $cmd\n";
}

system($cmd);

unlink $conffile;
