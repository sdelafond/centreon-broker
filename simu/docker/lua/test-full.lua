--package.path = package.path .. ";/home/admin/?.lua"
local mysql = require "luasql.mysql"

local simu = {
  input_file = "/usr/share/centreon-broker/lua/export-all.log",
  step = 0,
  host_count = 1,
  poller_count = 1,
  conn = nil,
  stack = {},
  step = 1,
}

local step = {
  require('neb.instances'),
  require('neb.hosts'),
  require('neb.finish'),
}

step[1].count = 1
step[2].count = 10

function os.capture(cmd, raw)
  local f = assert(io.popen(cmd, 'r'))
  local s = assert(f:read('*a'))
  f:close()
  if raw then return s end
  s = string.gsub(s, '^%s+', '')
  s = string.gsub(s, '%s+$', '')
  s = string.gsub(s, '[\n\r]+', ' ')
  return s
end

function init(conf)
  os.remove("/tmp/simu.log")
  broker_log:set_parameters(3, "/tmp/simu.log")
  local env = mysql.mysql()
  simu.conn = env:connect('centreon_storage', 'root', 'root', '172.17.0.1', 3306)
  if not simu.conn then
    broker_log:error(0, "No connection to database")
    error("No connection to database")
  end

--  -- We are waiting for a string here
--  if conf.input_file then
--    simu.input_file = conf.input_file
--  end
--  simu.f = io.open(simu.input_file, "r")
end

function read()
  if #simu.stack == 0 then
    if not simu.done then
      if step[simu.step] then
        step[simu.step].build(simu.stack, step[simu.step].count)
        simu.done = true
      else
        broker_log:info(0, "No more step 1")
      end
    else
      -- Check of instance in db
      if step[simu.step].check(simu.conn) then
        simu.step = simu.step + 1
        if step[simu.step] then
          step[simu.step].build(simu.stack, step[simu.step].count)
        else
          broker_log:info(0, "No more step 2")
        end
      end
    end
  end

  if #simu.stack > 0 then
    broker_log:info(0, broker.json_encode(simu.stack[1]))
    return table.remove(simu.stack, 1)
  else
    broker_log:info(0, "FINISHED...")
  end
end
