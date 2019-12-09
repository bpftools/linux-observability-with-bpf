# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

$bootstrap=<<SCRIPT
apt-get install bpfcc-tools linux-headers-$(uname -r)
SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  num_machines = 2
  net_ip = "192.168.33.10"

  config.vm.define "bpfbook" do |net|
  net.vm.box = "ubuntu/eoan64"
  net_index = 1
  net.vm.hostname = "bpfbook"
  net.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--memory", "1024"]
  end
  net.vm.network :private_network, ip: "#{net_ip}"
  net.vm.provision :shell, inline: $bootstrap, :args => "#{net_ip}"
end
end

