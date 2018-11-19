local function build(id, name, engine, pid)
  local now = os.time()
  local retval = {
    category = 1,
    element = 15,
    type = 65551,
    instance_id = id,
    name = name,
    active_host_checks = 1,
    active_service_checks = 1,
    check_hosts_freshness = 0,
    check_services_freshness = 1,
    engine = engine,
    event_handlers = 1,
    flap_detection = 0,
    last_alive = now,
    notifications = 1,
    passive_host_checks = 1,
    passive_service_checks = 1,
    pid = pid,
    running = 1,
    start_time = now,
    version = "1.8.1"
  }
  return retval
end

local instances = {
  -- id: instance id
  -- name: instance name
  -- engine: Monitoring engine name in this instance
  -- pid: Monitoring engine pid
  --
  -- return: a neb::instance event
  build = function (stack, poller_count)
    broker_log:info(0, "BUILD_INSTANCES ; poller_count = "
        .. tostring(poller_count))
    for i = 1,poller_count do
      table.insert(
              stack,
              build(1, "Central", "Centreon Engine " .. i, 600 + i))
    end
  end,
  check = function (conn)
    broker_log:info(0, "CHECK_INSTANCES")
    local retval = true
    local cursor, error_str = conn:execute([[SELECT instance_id, name from instances]])
    local row = cursor:fetch({}, "a")
    if not row then
      broker_log:error(0, "instances table empty")
      retval = false
    else
      if tonumber(row.instance_id) ~= 1 or row.name ~= "Central" then
        broker_log:error(0, "Bad data in instances table: instance_id = "
            .. row.instance_id .. " name = " .. row.name)
        retval = false
      end
    end
    if retval then
      broker_log:info(0, "CHECK_INSTANCES => DONE")
    else
      broker_log:info(0, "CHECK_INSTANCES => NOT DONE")
    end
    return retval
  end
}

return instances
