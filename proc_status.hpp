#ifndef __PROC_STATUS_HPP__
#define __PROC_STATUS_HPP__
#include <fstream>
#include <stdexcept>
#include <vector>

namespace proc_status {
class proc_status{
	std::string raw;

	std::string name;
	std::string umask;
	std::string state;
	unsigned tid;
	unsigned ngid;
	unsigned pid;
	unsigned ppid;
	unsigned tracer_pid;
	std::string uid;
	std::string gid;
	unsigned fd_size;
	std::vector<unsigned> groups;
	unsigned vm_peak;
	unsigned vm_size;
	unsigned vm_lck;
	unsigned vm_pin;
	unsigned vm_hwm;
	unsigned vm_rss;
	unsigned rss_anon;
	unsigned rss_file;
	unsigned rss_shmem;
	unsigned vm_data;
	unsigned vm_stk;
	unsigned vm_exe;
	unsigned vm_lib;
	unsigned vm_pte;
	unsigned vm_swap;
	unsigned threads;
	unsigned sig_q, sig_q_max;

	inline void load_info(const std::string dir){
		std::ifstream ifs("/proc/" + dir + "/status");
		if(!ifs){
			throw std::runtime_error("Not a valid pid : " + dir);
		}
	}
public:
	inline void load_self_info(){
		this->load_info("self");
	}

	inline void load_pid_info(const unsigned p){
		this->load_info(std::to_string(p));
	}

};
} // namespace proc_status

#endif /* end of include guard */
