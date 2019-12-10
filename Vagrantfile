# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

$bootstrap=<<SCRIPT
dnf install make glibc-devel.i686 elfutils-libelf-devel wget tar clang bcc strace kernel-devel-5.0.9-301.fc30 -y
SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  num_machines = 2
  net_ip = "192.168.33.10"

  config.vm.define "bpfbook" do |net|
  config.vm.box = "fedora/30-cloud-base"
  config.vm.box_version = "30.20190425.0"
  net_index = 1
  config.vm.hostname = "bpfbook"
  config.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--memory", "1024"]
  end
  config.vm.network :private_network, ip: "#{net_ip}"
  config.vm.provision :shell, inline: $bootstrap, :args => "#{net_ip}"
end
end

