from cyaron import *



xxx = IO(file_prefix="rtfz", data_id=10)
out = Vector.random(1500, [(-40000,40000), (-40000,40000), (-40000,40000)], 0)
xxx.input_write(1500,30)
xxx.input_write(out)
