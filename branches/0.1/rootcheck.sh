EX_NOPERM=77;
if [ "$(id -u)" != "0" ];
then
	echo "This action could only be taken as root";
	exit $EX_NOPERM;
fi
