terraform {
    required_providers {
    proxmox = {
      source = "bpg/proxmox"
      version = "0.73.1"
    }
  }
}

provider "proxmox" {
 endpoint = "https://192.168.3.88:8006/"

  username = "root@pam"

  password = "Passw0rd"



  insecure = true


  ssh {
    agent = true
  }
}

data "local_file" "ssh_public_key" {
  filename = "/home/nikol/.ssh/id_ed25519.pub"
}

resource "proxmox_virtual_environment_vm" "ubuntu_vm" {
  count     = 3
  name      = "test-ubuntu-${count.index + 1}"
  node_name = "nime"

  initialization {
    ip_config {
      ipv4 {
        address = "192.168.3.${120 + count.index}/24"
        gateway = "192.168.3.1"
      }
    }

    user_account {
      username = "ubuntu"
      keys     = [trimspace(data.local_file.ssh_public_key.content)]
    }
  }

  disk {
    datastore_id = "local-lvm"
    file_id      = proxmox_virtual_environment_download_file.ubuntu_cloud_image.id
    interface    = "virtio0"
    iothread     = true
    discard      = "on"
    size         = 50
  }

  network_device {
    bridge = "vmbr0"
  }
}

resource "proxmox_virtual_environment_download_file" "ubuntu_cloud_image" {
  content_type = "iso"
  datastore_id = "local"
  node_name    = "nime"

  url = "https://cloud-images.ubuntu.com/jammy/current/jammy-server-cloudimg-amd64.img"
}
