The `setup-dev-env.sh` has a couple of utility shell function to make the development work easier with the VirtualBox VM provided by the book. If you need an IDE to work on the code, probably we want to run your IDE on your host machine and sync up the code in the VM. `setup-dev-env.sh` can help on it.

To load the shell functions:
```
source setup-dev-env.sh || true
```

To sync the local code and files with the VM:
```
rsync2VM
```

To sync the local code and files in the VM back:
```
rsync2host
```

To run a shell command in the VM:
```
runRCMD
```
