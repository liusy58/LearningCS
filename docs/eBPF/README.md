



## Map

### Map Helper Functions

|Function Name|Functionality|Space| Notes|
|-|-|-|-|
|`bpf(BPF_MAP_CREATE,,)`|_create a map_ | Kernel & User| |
|`bpf_map_update_elem()`|_update elements_ | Kernel & User | `BPF_NOEXIST`: successs only when the key **not** exist ; `BPF_EXIST`: successs only when the key exist  |
|`bpf_map_lookup_elem`|_read elements from a BPF map_|Kernel & User| |
|`bpf_map_delete_element`|_removing an element from a BPF map_|Kernel & User||
|`bpf_map_get_next_key`|_help iterate a map_|User||
|`bpf_map_lookup_and_delete_element`|_looking up and deleting elements_|Kernel||
|`bpf_spin_lock`|_lock an element_||||
|`bpf_spin_unlock`|_unlock an elemnt_||||


### Types pf BPF Maps

|Type|Functionality|Notes|
|-|-|-|
|`BPF_MAP_TYPE_HASH`| |Useful for keeping structured data that’s read frequently.|
|`BPF_MAP_TYPE_ARRAY`|Array maps are commonly used to store information that can change in value, but it’s usually fixed in behavior.|A disadvantage of using array maps is that the elements in the map cannot be removed and you cannot make the array smaller than it is.|
|`BPF_MAP_TYPE_PROG_ARRAY`|You can use this type of map to store references to BPF programs using their file descriptor identifiers which makes tail call possible.||
|`BPF_MAP_TYPE_HASH`||This type of map is useful if your BPF program collects metrics and aggregates them in hash-table maps.|
|`BPF_MAP_TYPE_ARRAY`||Useful for for high-performant lookups and aggregations.|
|`BPF_MAP_TYPE_STACK_TRACE`|stores stack traces from the running process||
|`BPF_MAP_TYPE_CGROUP_ARRAY`|stores references to cgroups.|This map is useful when you want to share cgroup references between BPF maps for controlling traffic, debugging, and testing.||
|`BPF_MAP_TYPE_LRU_HASH` / `BPF_MAP_TYPE_LRU_PERCPU_HASH`|If the map is full, these maps will erase elements that are not used frequently to make room for new elements in the map.||
|`BPF_MAP_TYPE_LPM_TRIE`|LPM trie maps are types of map that use longest prefix match (LPM) to look up elements in the map.|Require key sizes to be multiples of eight and in a range from 8 to 2,048.|
|`BPF_MAP_TYPE_ARRAY_OF_MAPS` / `BPF_MAP_TYPE_HASH_OF_MAPS`| store references to other maps |These types of maps are useful when you want to be able to replace entire maps at runtime.|
|`BPF_MAP_TYPE_DEVMAP`|stores references to network devices.|Useful for network applications that want to manipulate traffic at the kernel level.|
|`BPF_MAP_TYPE_XSKMAP`|stores references to open sockets.|useful for forwarding packets|
|`BPF_MAP_TYPE_SOCKMAP` / `BPF_MAP_TYPE_SOCKHASH`|store references to open sockets in the kernel.||
|`BPF_MAP_TYPE_CGROUP_STORAGE` / `BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE`|||
