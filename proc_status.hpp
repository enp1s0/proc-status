#ifndef __PROC_STATUS_HPP__
#define __PROC_STATUS_HPP__
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace proc_status {
class proc_status{
	std::string raw;

	std::string name;
	std::string umask;
	std::string state;
	unsigned tgid;
	unsigned ngid;
	unsigned pid;
	unsigned ppid;
	unsigned tracer_pid;
	unsigned real_uid;
	unsigned effective_uid;
	unsigned saved_uid;
	unsigned filesystem_uid;
	unsigned real_gid;
	unsigned effective_gid;
	unsigned saved_gid;
	unsigned filesystem_gid;
	unsigned fd_size;
	std::vector<std::string> groups;
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
	std::string sig_pnd;
	std::string shd_pnd;
	std::string sig_blk;
	std::string sig_ign;
	std::string sig_cgt;
	std::string cap_inh;
	std::string cap_prm;
	std::string cap_eff;
	std::string cap_bnd;
	std::string cap_amb;
	unsigned seccomp;
	std::string speculation_store_bypass;
	std::string cpus_allowed;
	std::string cpus_allowed_list;
	std::string mems_allowed;
	std::string mems_allowed_list;
	unsigned voluntary_ctxt_switches;
	unsigned nonvoluntary_ctxt_switches;

	inline std::vector<std::string> split_item(const std::string str){
		const auto colon_pos = str.find(":");
		const auto item_name = str.substr(0, colon_pos);
		const auto content_pos = str.find_first_not_of(" ", colon_pos + 2);
		const auto item_content = str.substr(content_pos);
		std::vector<std::string> str_list;
		str_list.push_back(item_name);
		str_list.push_back(item_content);
		return str_list;
	}
	inline std::vector<std::string> split_string(const std::string str, const std::string separator = " "){
		const auto separator_length = separator.length();

		std::vector<std::string> str_list;
		if(separator_length == 0){
			str_list.push_back(str);
		}else{
			auto offset = std::string::size_type(0);
			while(1){
				const auto pos = str.find(separator, offset);
				if(pos == std::string::npos){
					str_list.push_back(str.substr(offset));
					break;
				}
				str_list.push_back(str.substr(offset, pos - offset));
				offset = pos + separator_length;
			}
		}
		return str_list;
	}

	inline void load_info(const std::string dir){
		std::ifstream ifs("/proc/" + dir + "/status");
		if(!ifs){
			throw std::runtime_error("Not a valid pid : " + dir);
		}
		std::string buffer;
		while(std::getline(ifs, buffer)){
			if(raw.length() != 0)
				raw += "\n";
			raw += buffer;

			const auto item = split_item(buffer);
			const auto item_name = item[0];
			const auto item_content = item[1];

			if(item_name == "Name"){
				name = item_content;
			}else if(item_name == "Umask"){
				umask = item_content;
			}else if(item_name == "State"){
				state = item_content;
			}else if(item_name == "Tgid"){
				tgid = std::stoul(item_content);
			}else if(item_name == "Ngid"){
				ngid = std::stoul(item_content);
			}else if(item_name == "Pid"){
				pid = std::stoul(item_content);
			}else if(item_name == "PPid"){
				ppid = std::stoul(item_content);
			}else if(item_name == "TracerPid"){
				tracer_pid = std::stoul(item_content);
			}else if(item_name == "Uid"){
				const auto contents_list = split_string(item_content);
				real_uid = std::stoul(contents_list[0]);
				effective_uid = std::stoul(contents_list[0]);
				saved_uid = std::stoul(contents_list[0]);
				filesystem_uid = std::stoul(contents_list[0]);
			}else if(item_name == "Gid"){
				const auto contents_list = split_string(item_content);
				real_gid = std::stoul(contents_list[0]);
				effective_gid = std::stoul(contents_list[0]);
				saved_gid = std::stoul(contents_list[0]);
				filesystem_gid = std::stoul(contents_list[0]);
			}else if(item_name == "FDSize"){
				fd_size = std::stoul(item_content);
			}else if(item_name == "Groups"){
				groups = split_string(item_content);
			}else if(item_name == "VmPeak"){
				const auto contents_list = split_string(item_content);
				vm_peak = std::stoul(contents_list[0]);
			}else if(item_name == "VmSize"){
				const auto contents_list = split_string(item_content);
				vm_size = std::stoul(contents_list[0]);
			}else if(item_name == "VmLck"){
				const auto contents_list = split_string(item_content);
				vm_lck = std::stoul(contents_list[0]);
			}else if(item_name == "VmPin"){
				const auto contents_list = split_string(item_content);
				vm_pin = std::stoul(contents_list[0]);
			}else if(item_name == "VmHWM"){
				const auto contents_list = split_string(item_content);
				vm_hwm = std::stoul(contents_list[0]);
			}else if(item_name == "VmRSS"){
				const auto contents_list = split_string(item_content);
				vm_rss = std::stoul(contents_list[0]);
			}else if(item_name == "RssAnon"){
				const auto contents_list = split_string(item_content);
				rss_anon = std::stoul(contents_list[0]);
			}else if(item_name == "RssFile"){
				const auto contents_list = split_string(item_content);
				rss_file = std::stoul(contents_list[0]);
			}else if(item_name == "RssShmem"){
				const auto contents_list = split_string(item_content);
				rss_shmem = std::stoul(contents_list[0]);
			}else if(item_name == "VmData"){
				const auto contents_list = split_string(item_content);
				vm_data = std::stoul(contents_list[0]);
			}else if(item_name == "VmStk"){
				const auto contents_list = split_string(item_content);
				vm_stk = std::stoul(contents_list[0]);
			}else if(item_name == "VmExe"){
				const auto contents_list = split_string(item_content);
				vm_exe = std::stoul(contents_list[0]);
			}else if(item_name == "VmLib"){
				const auto contents_list = split_string(item_content);
				vm_lib = std::stoul(contents_list[0]);
			}else if(item_name == "VmPTE"){
				const auto contents_list = split_string(item_content);
				vm_pte = std::stoul(contents_list[0]);
			}else if(item_name == "VmSwap"){
				const auto contents_list = split_string(item_content);
				vm_swap = std::stoul(contents_list[0]);
			}else if(item_name == "Threads"){
				threads = std::stoul(item_content);
			}else if(item_name == "SigQ"){
				const auto contents_list = split_string(item_content, "/");
				sig_q = std::stoul(contents_list[0]);
				sig_q_max = std::stoul(contents_list[1]);
			}else if(item_name == "SigPnd"){
				sig_pnd = item_content;
			}else if(item_name == "ShdPnd"){
				shd_pnd = item_content;
			}else if(item_name == "SigBlk"){
				sig_blk = item_content;
			}else if(item_name == "SigIgn"){
				sig_ign = item_content;
			}else if(item_name == "SigCgt"){
				sig_cgt = item_content;
			}else if(item_name == "CapInh"){
				cap_inh = item_content;
			}else if(item_name == "CapPrm"){
				cap_prm = item_content;
			}else if(item_name == "CapEff"){
				cap_eff = item_content;
			}else if(item_name == "CapBnd"){
				cap_bnd = item_content;
			}else if(item_name == "CapAmb"){
				cap_amb = item_content;
			}else if(item_name == "Seccomp"){
				seccomp = std::stoul(item_content);
			}else if(item_name == "Speculation_Store_Bypass"){
				speculation_store_bypass = item_content;
			}else if(item_name == "Cpus_allowed"){
				cpus_allowed = item_content;
			}else if(item_name == "Cpus_allowed_list"){
				cpus_allowed_list = item_content;
			}else if(item_name == "Mems_allowed"){
				mems_allowed = item_content;
			}else if(item_name == "Mems_allowed_list"){
				mems_allowed_list = item_content;
			}else if(item_name == "voluntary_ctxt_switches"){
				voluntary_ctxt_switches = std::stoul(item_content);
			}else if(item_name == "nonvoluntary_ctxt_switches"){
				nonvoluntary_ctxt_switches = std::stoul(item_content);
			}
		}
		ifs.close();
	}
public:
	inline void load_self_info(){
		this->load_info("self");
	}

	inline void load_pid_info(const unsigned p){
		this->load_info(std::to_string(p));
	}
	
	std::string get_raw() const {return raw;}
	std::string get_Name() const {return name;}
	std::string get_Umask() const {return umask;}
	std::string get_State() const {return state;}
	unsigned get_Tgid() const {return tgid;}
	unsigned get_Ngid() const {return ngid;}
	unsigned get_Pid() const {return pid;}
	unsigned get_PPid() const {return ppid;}
	unsigned get_TracerPid() const {return tracer_pid;}
	unsigned get_Uid_real() const {return real_uid;}
	unsigned get_Uid_effective() const {return effective_uid;}
	unsigned get_Uid_saved() const {return saved_uid;}
	unsigned get_Uid_filesystem() const {return filesystem_uid;}
	unsigned get_Gid_real() const {return real_gid;}
	unsigned get_Gid_effective() const {return effective_gid;}
	unsigned get_Gid_saved() const {return saved_gid;}
	unsigned get_Gid_filesystem() const {return filesystem_gid;}
	unsigned get_FDSize() const {return fd_size;}
	std::vector<std::string> get_Groups() const {return groups;}
	unsigned get_VmPeak() const {return vm_peak;}
	unsigned get_VmSize() const {return vm_size;}
	unsigned get_VmLck() const {return vm_lck;}
	unsigned get_VmPin() const {return vm_pin;}
	unsigned get_VmHWM() const {return vm_hwm;}
	unsigned get_VmRSS() const {return vm_rss;}
	unsigned get_RssAnon() const {return rss_anon;}
	unsigned get_RssFile() const {return rss_file;}
	unsigned get_RssShmem() const {return rss_shmem;}
	unsigned get_VmData() const {return vm_data;}
	unsigned get_VmStk() const {return vm_stk;}
	unsigned get_VmExe() const {return vm_exe;}
	unsigned get_VmLib() const {return vm_lib;}
	unsigned get_VmPTE() const {return vm_pte;}
	unsigned get_VmSwap() const {return vm_swap;}
	unsigned get_Threads() const {return threads;}
	unsigned get_SigQ() const {return sig_q;}
	unsigned get_SigQ_max() const {return sig_q_max;}
	std::string get_SigPnd() const {return sig_pnd;}
	std::string get_ShdPnd() const {return shd_pnd;}
	std::string get_SigBlk() const {return sig_blk;}
	std::string get_SigIgn() const {return sig_ign;}
	std::string get_SigCgt() const {return sig_cgt;}
	std::string get_CapInh() const {return cap_inh;}
	std::string get_CapPrm() const {return cap_prm;}
	std::string get_CapEff() const {return cap_eff;}
	std::string get_CapBnd() const {return cap_bnd;}
	std::string get_CapAmb() const {return cap_amb;}
	unsigned get_Seccomp() const {return seccomp;}
	std::string get_Speculation_Store_Bypass() const {return speculation_store_bypass;}
	std::string get_Cpus_allowed() const {return cpus_allowed;}
	std::string get_Cpus_allowed_list() const {return cpus_allowed_list;}
	std::string get_Mems_allowed() const {return mems_allowed;}
	std::string get_Mems_allowed_list() const {return mems_allowed_list;}
	unsigned get_voluntary_ctxt_switches() const {return voluntary_ctxt_switches;}
	unsigned get_nonvoluntary_ctxt_switches() const {return nonvoluntary_ctxt_switches;}
};
} // namespace proc_status

#endif /* end of include guard */
