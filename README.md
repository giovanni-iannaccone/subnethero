# 🛰️ Subnetter

Subnetter is a powerful C-based command-line tool designed to help network administrators and IT professionals generate subnetting tables and manage IP ranges for different network configurations. Whether you're using a flat approach, FLSM (Fixed-Length Subnet Mask), or VLSM (Variable-Length Subnet Mask), this tool will streamline the process of subnetting and ensure you get precise network breakdowns.

## 🧮 Features
- Multiple subnetting approaches (flat, flsm, vlsm)
- Simple command-line interface
- Displays subnet information in a clear tabular format
- Generates subnetting tables with efficient algorithm.

## 📡 Installation
1. Download subnetter with git
```sh
git clone https://github.com/giovanni-iannaccone/subnetter
cd subnetter
```

2. Compile it using make
```sh
make all
```

## 💡 Command-Line Usage

```
subnetter v1.0

Usage:
subnetter [-t | -f | -v] -c cidr -i ip -d n {n devices for each network}

Options:
  -t | --flat        use the flat approach
  -f | --flsm        use the flsm approach
  -v | --vlsm        use the vlsm approach

  -i | --ip          specify the IP of the base network
  -c | --cidr        the CIDR of the original network
  -d | --devs        Number of subnetworks (followed by n devices for each network)

Example:
subnetter -v -c 24 -i 192.168.1.0 -d 3 64 5 15
```

### Parameters:

- `-t` | `--flat` <br/>
This option uses a flat approach to subnetting, dividing the network into equal-sized subnets.

- `-f` | `--flsm` <br/>
This option applies the Fixed-Length Subnet Mask method, creating subnets of the same size based on the given number of devices.

- `-v` | `--vlsm` <br/>
This option uses the Variable-Length Subnet Mask method, where each subnet can vary in size according to the number of devices specified.

- `-i` | `--ip` <br/>
Enter the starting IP address of the network you want to subnet (e.g., 192.168.1.0).

- `-c` | `--cidr` <br/>
Specify the CIDR notation for the original network (e.g., /24).

- `-d` | `--devs` <br/>
Define the number of subnets you need, followed by the number of devices in each subnet. The tool will calculate the necessary subnet masks.

## 🛸 Output Format

For each subnet, the output will generate the following columns:

| IP           |   CIDR  |	Broadcast   |   Start      |    End  	  | Free from	 |    to        |
|--------------|---------|--------------|--------------|--------------|--------------|--------------|
| 192.168.1.0  |   /26	 | 192.168.1.63	| 192.168.1.1  | 192.168.1.62 | 192.168.1.3	 | 192.168.1.62 |
| 192.168.1.64 |   /29	 | 192.168.1.71	| 192.168.1.65 | 192.168.1.70 |	192.168.1.66 | 192.168.1.69 |
| 192.168.1.72 |   /28	 | 192.168.1.87	| 192.168.1.73 | 192.168.1.86 |	192.168.1.74 | 192.168.1.85 |

## 🧩 Contributing
We welcome contributions! Please follow these steps:

1. Fork the repository.
2. Create a new branch ( using <a href="https://medium.com/@abhay.pixolo/naming-conventions-for-git-branches-a-cheatsheet-8549feca2534">this</a> convention).
3. Make your changes and commit them with descriptive messages.
4. Push your changes to your fork.
5. Create a pull request to the main repository.

## ⚖ License
This project is licensed under the GPL-3.0 License. See the LICENSE file for details.

## ⚔ Contact
- For any inquiries or support, please contact <a href="mailto:iannacconegiovanni444@gmail.com"> iannacconegiovanni444@gmail.com </a>.
- Visit my site for more informations about me and my work <a href="https://giovanni-iannaccone.gith
ub.io" target=”_blank” rel="noopener noreferrer"> https://giovanni-iannaccone.github.io </a>