#include "Logic/Mailbox/Mailbox.h"

namespace logic
{

void Mailbox::Send(std::shared_ptr<Mail> i_mail)
{
	m_mails.push(i_mail);
}

void Mailbox::Send(Mail i_mail)
{
	m_mails.push(std::make_shared<Mail>(i_mail));
}

std::shared_ptr<Mail> Mailbox::Receive()
{
	std::shared_ptr<Mail> mail = m_mails.top();
	m_mails.pop();
	return mail;
}

bool Mailbox::IsEmpty()
{
	return m_mails.empty();
}

} // namespace logic