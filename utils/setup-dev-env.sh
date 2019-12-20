#set -x
RSYNCOPTS=" -zavhr --exclude={'.git*','.git/','.vagrant*'} "

OSNAME=$(uname)
[ ${OSNAME} != "Darwin" ] && [ ${OSNAME} != "Linux" ] && \
  echo -e "\033[33m\033[5m $BASH_SOURCE probably won't work on your OS ${OSNAME} \033[0m" && exit

VMIP=$(grep "net_ip = " Vagrantfile | cut -d "\"" -f 2)
[[ -z $VMIP ]] && echo "Failed to get the VM IP, something is wrong" && exit
echo -e "The VM IP:\t${VMIP}"

REMOTEID=vagrant@$VMIP
GITINVM=${REMOTEID}:/vagrant/
SOURCE="${BASH_SOURCE[0]}"
# or grealpath on Mac or realpath on Linux
GITINHOST=$( cd "$(dirname $SOURCE)" ; pwd -P )
GITINHOST="${GITINHOST}/"
echo -e "Local\tlinux-observability-with-bpf path:\t$GITINHOST"
echo -e "Remote\tlinux-observability-with-bpf path:\t$GITINVM"


which ssh-copy-id && (ssh-copy-id $REMOTEID && echo -e "Copied ssh pub key to removed server as\t $REMOTEID") \
                  || (ssh $REMOTEID "echo \"`cat ~/.ssh/id_rsa.pub`\" >> .ssh/authorized_keys")

function rsync2host {
    echo Syncing from $GITINVM to $GITINHOST ...
    rsync $RSYNCOPTS $GITINVM $GITINHOST > /tmp/rsync2host.log
    echo Syncing from $GITINVM to $GITINHOST is done!
}

function rsync2VM {
    echo Syncing from $GITINHOST to $GITINVM ...
    rsync $RSYNCOPTS $GITINHOST $GITINVM > /tmp/rsync2VM.log
    echo Syncing from $GITINHOST to $GITINVM is done!
}

function runRCMD {
  echo Running $@ on $REMOTEID
  ssh $REMOTEID "$@"
}
