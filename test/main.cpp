#include <iostream>
#include <iomanip>
#include "proc_status.hpp"

#define PRINT_INFO(info) std::cout<<std::setw(space)<<#info;std::cout<<" : "<<ps.get_##info()<<std::endl

constexpr int space = 28;

int main(){
	proc_status::proc_status ps;
	ps.load_self_info();

	PRINT_INFO(Name);
	PRINT_INFO(Umask);
	PRINT_INFO(State);
	PRINT_INFO(Tgid);
	PRINT_INFO(Ngid);
	PRINT_INFO(Pid);
	PRINT_INFO(PPid);
	PRINT_INFO(TracerPid);
	PRINT_INFO(Uid_real);
	PRINT_INFO(Uid_effective);
	PRINT_INFO(Uid_saved);
	PRINT_INFO(Uid_filesystem);
	PRINT_INFO(Gid_real);
	PRINT_INFO(Gid_effective);
	PRINT_INFO(Gid_saved);
	PRINT_INFO(Gid_filesystem);
	PRINT_INFO(FDSize);
	std::cout<<std::setw(space)<<"Groups";std::cout<<" : ";
	for(const auto &g : ps.get_Groups()) std::cout<<g<<" ";
	std::cout<<std::endl;
	PRINT_INFO(VmPeak);
	PRINT_INFO(VmSize);
	PRINT_INFO(VmLck);
	PRINT_INFO(VmPin);
	PRINT_INFO(VmHWM);
	PRINT_INFO(VmRSS);
	PRINT_INFO(RssAnon);
	PRINT_INFO(RssFile);
	PRINT_INFO(RssShmem);
	PRINT_INFO(VmData);
	PRINT_INFO(VmStk);
	PRINT_INFO(VmExe);
	PRINT_INFO(VmLib);
	PRINT_INFO(VmPTE);
	PRINT_INFO(VmSwap);
	PRINT_INFO(Threads);
	PRINT_INFO(SigQ);
	PRINT_INFO(SigQ_max);
	PRINT_INFO(SigPnd);
	PRINT_INFO(ShdPnd);
	PRINT_INFO(SigBlk);
	PRINT_INFO(SigIgn);
	PRINT_INFO(SigCgt);
	PRINT_INFO(CapInh);
	PRINT_INFO(CapPrm);
	PRINT_INFO(CapEff);
	PRINT_INFO(CapBnd);
	PRINT_INFO(CapAmb);
	PRINT_INFO(Seccomp);
	PRINT_INFO(Speculation_Store_Bypass);
	PRINT_INFO(Cpus_allowed);
	PRINT_INFO(Cpus_allowed_list);
	PRINT_INFO(Mems_allowed);
	PRINT_INFO(Mems_allowed_list);
	PRINT_INFO(voluntary_ctxt_switches);
	PRINT_INFO(nonvoluntary_ctxt_switches);
}
