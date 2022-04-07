from smbus2 import SMBus

i2c_addr = 60

with SMBus(1) as bus:
    data = [0, 1, 2, 3, 4, 5]
    bus.write_i2c_block_data(i2c_addr, 0, data)
