set -e

SAVEFILE=map_pinning_save
FETCHFILE=map_pinning_fetch
BPFMAP=/sys/fs/bpf/my_array
WHO=$(whoami)

[[ ${WHO} != "root" ]] && echo "You need to run it as root user or sudo $0" && exit 1

rm -f $SAVEFILE $FETCHFILE $BPFMAP

make execable BPFCODE=$SAVEFILE && [[ -x ./$SAVEFILE ]] && echo "$SAVEFILE is ready"
make execable BPFCODE=$FETCHFILE && [[ -x ./$FETCHFILE ]] && echo "$FETCHFILE is ready"

./$SAVEFILE && ls $BPFMAP > /dev/null && echo "$BPFMAP has been created"
./$FETCHFILE
