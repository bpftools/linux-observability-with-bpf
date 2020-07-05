# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

$bootstrap=<<SCRIPT
dnf install make glibc-devel.i686 elfutils-libelf-devel wget tar vim tmux jq systemtap-sdt-devel clang bcc strace kernel-devel-5.0.9-301.fc30 -y
SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
	ipv4 = "192.168.33.10"
	config.vm.define "bpfbook" do |fedora|
		fedora.vm.box = "fedora/30-cloud-base"
		fedora.vm.box_version = "30.20190425.0"
		net_index = 1
		fedora.vm.hostname = "bpfbook"
		fedora.vm.provider "virtualbox" do |vb|
			vb.customize ["modifyvm", :id, "--memory", "1024"]
		end
		fedora.vm.provider "libvirt" do |lv|
			lv.memory = 1024
		end
		fedora.vm.network :private_network, ip: "#{ipv4}"
		fedora.vm.provision :shell, inline: $bootstrap, :args => "#{ipv4}"
	end
end
