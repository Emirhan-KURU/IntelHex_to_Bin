def hex_to_bin(hex_file, bin_file):
    with open(hex_file, 'r') as hex_f:
        lines = hex_f.readlines()

    bin_data = bytearray()
    for line in lines:
        if line.startswith(':'):
            record_length = int(line[1:3], 16)
            address = int(line[3:7], 16)
            record_type = int(line[7:9], 16)
            data = line[9:9 + 2 * record_length]
            data_bytes = bytes.fromhex(data)
            bin_data.extend(data_bytes)

    with open(bin_file, 'wb') as bin_f:
        bin_f.write(bin_data)


hex_to_bin('GOREV_1_RTC_CLOCK.hex', 'output.bin')
