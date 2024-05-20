#pragma once
#include "Logic/Mailbox/IMailboxReceiver.h"
#include "Logic/Mailbox/IMailboxSender.h"
#include <stack>

namespace logic
{

class Mailbox:	public IMailboxReceiver,
				public IMailboxSender
{
public:
	void Send(std::shared_ptr<Mail> i_mail) override;
	void Send(Mail i_mail) override;

	std::shared_ptr<Mail> Receive() override;
	bool IsEmpty() override;

private:
	std::stack<std::shared_ptr<Mail>> m_mails;
};

} // namespace logic