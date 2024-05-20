#pragma once
#include "Logic/Mailbox/Mail.h"
#include <memory>

namespace logic
{

class IMailboxSender
{
public:
	virtual void Send(std::shared_ptr<Mail> i_mail) = 0;
	virtual void Send(Mail i_mail) = 0;
};

} // namespace logic