#pragma once
#include "Logic/Mailbox/Mail.h"
#include <memory>

namespace logic
{

class IMailboxReceiver
{
public:
	virtual std::shared_ptr<Mail> Receive() = 0;
	virtual bool IsEmpty() = 0;
};

} // namespace logic