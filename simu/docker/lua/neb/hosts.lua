local function build(id, instance_id, name, address)
  local now = os.time()
  local retval = {
    obsess_over_host = true,
    no_more_notifications = false,
    check_attempt = 1,
    icon_image_alt = "",
    enabled = true,
    host_id = id,
    state = 0,
    last_update = now,
    address = address,
    last_check = now - 10,
    notify_on_recovery = false,
    freshness_threshold = 0,
    default_active_checks = true,
    notification_period = "24x7",
    action_url = "",
    check_type = 0,
    retain_nonstatus_information = true,
    default_event_handler_enabled = true,
    last_time_up = now,
    instance_id = 1,
    check_period = "24x7",
    first_notification_delay = 0,
    last_hard_state = 0,
    event_handler = "",
    element = 12,
    stalk_on_down = false,
    latency = 0.134,
    low_flap_threshold = 0,
    last_state_change = now - 300,
    timezone = ":Europe/Paris",
    next_check = now + 300,
    should_be_scheduled = true,
    flap_detection = true,
    notify_on_down = true,
    notification_interval = 0,
    icon_image = "Brands/vmware.png",
    scheduled_downtime_depth = 0,
    notify_on_downtime = false,
    perfdata = "rta=2.326ms",
    output = "OK - vcenter-paris: rta 2.326ms, lost 0%\n",
    name = name,
    check_command = "check-bench-alive",
    acknowledgement_type = 0,
    statusmap_image = "Brands/vmware.png",
    execution_time = 0.018,
    acknowledged = false,
    stalk_on_up = false,
    active_checks = true,
    default_notify = false,
    stalk_on_unreachable = false,
    max_check_attempts = 5,
    retry_interval = 1,
    default_flap_detection = true,
    default_passive_checks = false,
    last_hard_state_change = now,
    notification_number = 0,
    display_name = "vcenter-paris",
    category = 1,
    high_flap_threshold = 0,
    check_interval = 3,
    alias = "vcenter-paris",
    passive_checks = false,
    checked = true,
    type = 65548,
    notify_on_unreachable = false,
    state_type = 1,
    notify_on_flapping = false,
    notes_url = "",
    notify = false,
    percent_state_change = 0,
    notes = "",
    flap_detection_on_unreachable = true,
    flap_detection_on_up = true,
    flapping = false,
    check_freshness = false,
    flap_detection_on_down = true,
    retain_status_information = true,
    event_handler_enabled = true
  }
  return retval
end

local hosts = {
  -- id: instance id
  -- name: instance name
  -- engine: Monitoring engine name in this instance
  -- pid: Monitoring engine pid
  --
  -- return: a neb::instance event
  build = function (stack, host_count)
    broker_log:info(0, "BUILD_HOSTS ; host_count = " .. tostring(host_count))
    for i = 1,host_count do
      table.insert(
              stack,
              build(i, 1, "host_" .. i, "1.2.3." .. i))
    end
    broker_log:info(0, "BUILD_HOSTS => FINISHED")
  end,
  check = function (conn)
    local now = os.time()
    broker_log:info(0, "CHECK_HOSTS")
    local retval = true
    local cursor, error_str = conn:execute([[SELECT name, last_update from hosts]])
    local row = cursor:fetch({}, "a")
    if not row then
      broker_log:error(0, "hosts table empty")
      retval = false
    else
      if not string.match(row.name, "host.*") then
        broker_log:error(0, "Bad data in hosts table: name = " .. row.name)
        retval = false
      else
        broker_log:info(0, "DELAY for HOSTS " .. row.name .. " : "
            .. (now - tonumber(row.last_update)))
      end
    end
    if retval then
      broker_log:info(0, "CHECK_HOSTS => DONE")
    else
      broker_log:info(0, "CHECK_HOSTS => NOT DONE")
    end
    return retval
  end
}

return hosts

